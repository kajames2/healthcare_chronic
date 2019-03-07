import numpy as np
import pandas as pd

filenames = ["employer_flat_60",
             "employer_flat_60_2",
             "actuarial_flat_60",
             "actuarial_flat_60_2"]
dfs = {filebase : pd.read_csv(filebase + "_rand_lives.csv") for filebase in filenames}
ages = range(1,31)

for col in ['Age', 'Cash', 'Shocks', 'ShockProb', 'NextFitness', 'InsurancePayout', 'BuyIns', 'Enjoyment', 'TotalJoy', 'JoySpending', 'FitnessSpending', 'InsuranceSpending', 'NextCash']:
    for filebase in filenames:
        means = [(dfs[filebase].loc[dfs[filebase]['Age'] == age])[col].mean() for age in ages]
        print("{0:35}".format(filebase) + "," + "{0:20}".format(col) + "," + ','.join(["{0:7.2f}".format(mean) for mean in means]))

#def get_death_period(life):
#    dead_pers = [int(row[0]) for row in life if float(row[header_indices["EndHealth"]]) <= 0]
#    if dead_pers:
#        return dead_pers[0]
#    else:
#        return max_age + 1

#death_periods = [get_death_period(life) for life in rand_lives]

#death_arr = [0]*(max_age + 1)
#for per in death_periods:
#    death_arr[per-1] += 1

#print(death_arr)
