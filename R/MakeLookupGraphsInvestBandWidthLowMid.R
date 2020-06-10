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

# E.G lowest .1 
BandWidth=.1

###########################

# generate probability table
Risk = matrix(NA, MaxT, 6)
for (t in 1:MaxT) {
  for (s in 0:5) {
    Risk[t,(s+1)] = exp(RateAge * t) + exp(RateShocks * s) + Constant 
  }
}

########################################

OutLow = matrix(NA,0,(4+MaxT))
OutMid = matrix(NA,0,(4+MaxT))
CN = c("Period", "Shocks", "Fit", "Invest")
for (t in 1:MaxT) {CN = c(CN, paste0("ModPer", t))}
colnames(OutLow) = CN
colnames(OutMid) = CN

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
        
        LB = (1 - BandWidth)/2
        UB = LB + BandWidth
        
        MID10 = matrix(NA, dim(Prop)[1], 7) 
        MID10[,7] = ifelse(Prop[,7]>LB, ifelse(Prop[,7]-LB<BandWidth, Prop[,7]-LB, BandWidth), 0)
        MID10[,6] = ifelse((Prop[,7]+Prop[,6])>LB, ifelse((Prop[,7]+Prop[,6]-LB)<BandWidth, (Prop[,7]+Prop[,6]-LB), BandWidth-MID10[,7]), 0)
        MID10[,5] = ifelse((Prop[,7]+Prop[,6]+Prop[,5])>LB, ifelse((Prop[,7]+Prop[,6]+Prop[,5]-LB)<BandWidth, (Prop[,7]+Prop[,6]+Prop[,5]-LB), BandWidth-MID10[,7]-MID10[,6]), 0)
        MID10[,4] = ifelse((Prop[,7]+Prop[,6]+Prop[,5]+Prop[,4])>LB, 
                           ifelse((Prop[,7]+Prop[,6]+Prop[,5]+Prop[,4]-LB)<BandWidth, (Prop[,7]+Prop[,6]+Prop[,5]+Prop[,4]-LB), BandWidth-MID10[,7]-MID10[,6]-MID10[,5]), 0)
        MID10[,3] = ifelse((Prop[,7]+Prop[,6]+Prop[,5]+Prop[,4]+Prop[,3])>LB, 
                           ifelse((Prop[,7]+Prop[,6]+Prop[,5]+Prop[,4]+Prop[,3]-LB)<BandWidth, (Prop[,7]+Prop[,6]+Prop[,5]+Prop[,4]+Prop[,3]-LB), 
                                  BandWidth-MID10[,7]-MID10[,6]-MID10[,5]-MID10[,4]), 0)
        MID10[,2] = ifelse((Prop[,7]+Prop[,6]+Prop[,5]+Prop[,4]+Prop[,3]+Prop[,2])>LB, 
                           ifelse((Prop[,7]+Prop[,6]+Prop[,5]+Prop[,4]+Prop[,3]+Prop[,2]-LB)<BandWidth, (Prop[,7]+Prop[,6]+Prop[,5]+Prop[,4]+Prop[,3]+Prop[,2]-LB), 
                                  BandWidth-MID10[,7]-MID10[,6]-MID10[,5]-MID10[,4]-MID10[,3]), 0)
        MID10[,1] = ifelse((Prop[,7]+Prop[,6]+Prop[,5]+Prop[,4]+Prop[,3]+Prop[,2]+Prop[,1]-LB)<BandWidth, Prop[,7]+Prop[,6]+Prop[,5]+Prop[,4]+Prop[,3]+Prop[,2]+Prop[,1]-LB, 
                           BandWidth-MID10[,7]-MID10[,6]-MID10[,5]-MID10[,4]-MID10[,3]-MID10[,2])
        
        LOW10 = matrix(NA, dim(Prop)[1], 7) 
        LOW10[,7] = ifelse(Prop[,7] < BandWidth, Prop[,7], BandWidth)
        LOW10[,6] = ifelse((Prop[,7]+Prop[,6]) < BandWidth, Prop[,6], BandWidth-LOW10[,7])
        LOW10[,5] = ifelse((Prop[,7]+Prop[,6]+Prop[,5]) < BandWidth, Prop[,5], BandWidth-LOW10[,7]-LOW10[,6])
        LOW10[,4] = ifelse((Prop[,7]+Prop[,6]+Prop[,5]+Prop[,4]) < BandWidth, Prop[,4], BandWidth-LOW10[,7]-LOW10[,6]-LOW10[,5])
        LOW10[,3] = ifelse((Prop[,7]+Prop[,6]+Prop[,5]+Prop[,4]+Prop[,3]) < BandWidth, Prop[,3], BandWidth-LOW10[,7]-LOW10[,6]-LOW10[,5]-LOW10[,4])
        LOW10[,2] = ifelse((Prop[,7]+Prop[,6]+Prop[,5]+Prop[,4]+Prop[,3]+Prop[,2]) < BandWidth, Prop[,2], BandWidth-LOW10[,7]-LOW10[,6]-LOW10[,5]-LOW10[,4]-LOW10[,3])
        LOW10[,1] = BandWidth-LOW10[,7]-LOW10[,6]-LOW10[,5]-LOW10[,4]-LOW10[,3]-LOW10[,2]
        
        MeanMid = 1*MID10[,2] + 2*MID10[,3] + 3*MID10[,4] + 4*MID10[,5] + 5*MID10[,6] + 6*MID10[,7] 
        MeanMid = MeanMid * 1/BandWidth
        MeanLow = 1*LOW10[,2] + 2*LOW10[,3] + 3*LOW10[,4] + 4*LOW10[,5] + 5*LOW10[,6] + 6*LOW10[,7]
        MeanLow = MeanLow * 1/BandWidth
        
        EnjoyMid = round((6 - MeanMid)/6, 3)
        EnjoyLow = round((6 - MeanLow)/6, 3)
        
        EnjoyMid = EnjoyMid[2:length(EnjoyMid)]
        if(t>1){EnjoyMid = c(rep(NA,(t-1)), EnjoyMid)}
        
        EnjoyLow = EnjoyLow[2:length(EnjoyLow)]
        if(t>1){EnjoyLow = c(rep(NA,(t-1)), EnjoyLow)}

        MidRow = matrix(c(t, s, f, i, EnjoyMid), 1 ,(4+MaxT))
        LowRow = matrix(c(t, s, f, i, EnjoyLow), 1 ,(4+MaxT))
        colnames(LowRow) = CN
        colnames(MidRow) = CN
        OutLow = rbind.data.frame(OutLow, LowRow)
        OutMid = rbind.data.frame(OutMid, MidRow)
      } # end invest loop
      
    } # end fit loop
    
  } # end Shock loop
  
} # end period loop
#stopCluster(cl)

colnames(OutLow) = CN
colnames(OutMid) = CN

write.csv(OutLow, "LookupFitLowEnd.csv", row.names = F)
