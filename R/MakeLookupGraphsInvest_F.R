# creates lookup table for graphs
setwd("R")
library(foreach)
library(doParallel)

# assumes fitness INVESTMENT will be the same for all future periods
###########################
# parameters
###########################

Degen = 1/3
FitPrice = 3
MaxT = 50

# Shock Probability Equation
# Pr = exp(RateAge * Age) + exp(RateShocks * Shocks) + Constant
RateAge = 0.02
RateShocks = 0.1
Constant = -1.95

# Prevention coefficent 
# MaxMod * Fit/(j + Fit)
MaxMod = 1.2
j = 40

###########################

# generate probability table
Risk = matrix(NA, MaxT, 6)
  for (t in 1:MaxT) {
    for (s in 0:5) {
      Risk[t,(s+1)] = exp(RateAge * t) + exp(RateShocks * s) + Constant 
    }
  }

########################################

Out = matrix(NA,0,(4+MaxT))
  CN = c("Period", "Shocks", "Fit", "Invest")
  for (t in 1:MaxT) {CN = c(CN, paste0("ModPer", t))}
  colnames(Out) = CN
 
  # set up paralell
  
  nc = detectCores()
  cl = makeCluster(nc-1)
  registerDoParallel(cl)
  
  #######################################
  
  
# period loop
foreach (t = 1:MaxT) %:% {
  print(paste0("t = ", t))
  
  # Shock loop
  foreach (s = 0:5) %do% {
    
    # fitness loop
    foreach (f = 0:80) %do% {
      
      # invest loop
      foreach (i = 0:100) %dopar% {
        
        Prop = matrix(c(rep(0, s), 1, rep(0, 6-s)), 1, 7)
        cn = NULL
        for (i in 0:6) {cn = c(cn, paste0("S=", i))}
        colnames(Prop) = cn
        Fit = f
        FitCoef = MaxMod * Fit/(j + Fit)
        Adj = (1-FitCoef)
        
        p=t
#        AdjRisk = Adj*Risk
        
        while (p<=MaxT) {
          NewRow = c(Prop[(p-t+1), 1] * (1 - min(1, Adj*Risk[(p-t+1),1])),
                     Prop[(p-t+1), 2] * (1 - min(1, Adj*Risk[(p-t+1),2])) + Prop[(p-t+1), 1] * min(1, Adj*Risk[(p-t+1),1]),
                     Prop[(p-t+1), 3] * (1 - min(1, Adj*Risk[(p-t+1),3])) + Prop[(p-t+1), 2] * min(1, Adj*Risk[(p-t+1),2]),
                     Prop[(p-t+1), 4] * (1 - min(1, Adj*Risk[(p-t+1),4])) + Prop[(p-t+1), 3] * min(1, Adj*Risk[(p-t+1),3]),
                     Prop[(p-t+1), 5] * (1 - min(1, Adj*Risk[(p-t+1),5])) + Prop[(p-t+1), 4] * min(1, Adj*Risk[(p-t+1),4]),
                     Prop[(p-t+1), 6] * (1 - min(1, Adj*Risk[(p-t+1),6])) + Prop[(p-t+1), 5] * min(1, Adj*Risk[(p-t+1),5]),
                     Prop[(p-t+1), 7]                                     + Prop[(p-t+1), 6] * min(1, Adj*Risk[(p-t+1),6]))
          Prop = rbind.data.frame(Prop, NewRow)

          p = p+1
          Fit = f*(1-Degen) + i/FitPrice
          FitCoef = MaxMod * Fit/(j + Fit)
          Adj = (1-FitCoef)
        } # while loop
        
        MeanShocks = 1*Prop[,2] + 2*Prop[,3] + 3*Prop[,4] + 4*Prop[,5] + 5*Prop[,6] + 6*Prop[,7] 
        EnjoyMod = (6 - MeanShocks)/6
        
        EnjoyMod = EnjoyMod[2:length(EnjoyMod)]
        if(t>1){EnjoyMod = c(rep(NA,(t-1)), EnjoyMod)}
        
        OutRow = c(t, s, f, i, EnjoyMod)
        Out = rbind.data.frame(Out, OutRow)
        
      } # end invest loop
      
    } # end fit loop
    
  } # end Shock loop
  
} # end period loop
  
stopImplicitCluster()
stopCluster(cl)
  
colnames(Out) = CN
write.csv(Out, "LookupInvestCurved.csv", row.names = F)
  