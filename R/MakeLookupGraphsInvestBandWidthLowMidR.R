# creates lookup table for graphs
 setwd("healthcare_chronic/R")
#library(foreach)
#library(doParallel)

# assumes fitness INVESTMENT will be the same for all future periods
###########################
# parameters
###########################

Degen = 1/3
FitPrice = 3
MaxT = 50

# Shock Probability Equation
# Pr = exp(RateAge * Age) + exp(RateShocks * Shocks) + Constant
RateAge = 0.005
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

Out = matrix(NA,0,(4+2*MaxT))
CN = c("Period", "Shocks", "Fit", "Invest")
for (t in 1:MaxT) {CN = c(CN, paste0("ModPer", t))}
for (t in 1:MaxT) {CN = c(CN, paste0("sdPer", t))}
colnames(Out) = CN

# set up paralell

#nc = detectCores()
#cl = makeCluster(nc)
#registerDoParallel(cl)

#######################################


# period loop
#foreach (t = 1:(MaxT-20)) %do% {
for(t in 1:(MaxT-20)){
    print(paste0("t = ", t))
  
  # Shock loop
#  foreach (s = 0:5) %do% {
  for(s in 0:5){
      
    # fitness loop
#    foreach (f = 0:80) %do% {
    for(f in 0:80){
        
      # invest loop
#      foreach (i = 0:100) %dopar% {
      for(i in 0:100){
          
        Prop = matrix(c(rep(0, s), 1, rep(0, 6-s)), 1, 7)
        cn = NULL
        for (i in 0:6) {cn = c(cn, paste0("S=", i))}
        colnames(Prop) = cn
        Fit = f
        FitCoef = MaxMod * Fit/(j + Fit)
        Adj = (1-FitCoef)
        
 #       foreach (p = t:MaxT) %do% {
        for(p in t:MaxT){
          Fit = f*(1-Degen) + i/FitPrice
          FitCoef = MaxMod * Fit/(j + Fit)
          Adj = (1-FitCoef)
          
          NewRow = c(Prop[(p-t+1), 1] * (1 - min(1, Adj*Risk[(p-t+1),1])),
                     Prop[(p-t+1), 2] * (1 - min(1, Adj*Risk[(p-t+1),2])) + Prop[(p-t+1), 1] * min(1, Adj*Risk[(p-t+1),1]),
                     Prop[(p-t+1), 3] * (1 - min(1, Adj*Risk[(p-t+1),3])) + Prop[(p-t+1), 2] * min(1, Adj*Risk[(p-t+1),2]),
                     Prop[(p-t+1), 4] * (1 - min(1, Adj*Risk[(p-t+1),4])) + Prop[(p-t+1), 3] * min(1, Adj*Risk[(p-t+1),3]),
                     Prop[(p-t+1), 5] * (1 - min(1, Adj*Risk[(p-t+1),5])) + Prop[(p-t+1), 4] * min(1, Adj*Risk[(p-t+1),4]),
                     Prop[(p-t+1), 6] * (1 - min(1, Adj*Risk[(p-t+1),6])) + Prop[(p-t+1), 5] * min(1, Adj*Risk[(p-t+1),5]),
                     Prop[(p-t+1), 7]                                     + Prop[(p-t+1), 6] * min(1, Adj*Risk[(p-t+1),6]))
          Prop = rbind.data.frame(Prop, NewRow)
        } # while loop
        
        MeanShocks = 1*Prop[,2] + 2*Prop[,3] + 3*Prop[,4] + 4*Prop[,5] + 5*Prop[,6] + 6*Prop[,7] 
        SDShocks = sqrt((0-MeanShocks)^2 *Prop[,1] + (1-MeanShocks)^2 *Prop[,2] + (2-MeanShocks)^2 *Prop[,3] + 
                          (3-MeanShocks)^2 *Prop[,4] + (4-MeanShocks)^2 *Prop[,5] + (5-MeanShocks)^2 *Prop[,6])
        
        EnjoyMod = (6 - MeanShocks)/6
        SDShocks = SDShocks/6
        
        EnjoyMod = EnjoyMod[2:length(EnjoyMod)]
        if(t>1){EnjoyMod = c(rep(NA,(t-1)), EnjoyMod)}
        
        SDShocks = SDShocks[2:length(SDShocks)]
        if(t>1){SDShocks = c(rep(NA,(t-1)), SDShocks)}
        
        OutRow = matrix(c(t, s, f, i, EnjoyMod, SDShocks), 1 ,(4+2*MaxT))
colnames(OutRow) = CN
write.csv(OutRow, "LookupFitBWMidLowNP.csv", row.names = F, append=T)
        Out = rbind.data.frame(Out, OutRow)
      } # end invest loop
      
    } # end fit loop
    
  } # end Shock loop
  
} # end period loop
#stopCluster(cl)

colnames(Out) = CN
write.csv(Out, "LookupFitBWMidLowEndNP.csv", row.names = F)
