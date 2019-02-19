import numpy as np
import pandas as pd

filenames = ["actuarial_flat_45_100",
             "actuarial_flat_60_100",
             "actuarial_flat_75_100",
             "actuarial_increasing_30_90_100",
             "actuarial_flat_45_95",
             "actuarial_flat_60_95",
             "actuarial_flat_75_95",
             "actuarial_increasing_30_90_95",
             "actuarial_flat_45_90",
             "actuarial_flat_60_90",
             "actuarial_flat_75_90",
             "actuarial_increasing_30_90_90"]
dfs = {filebase : pd.read_csv(filebase + "_rand_lives.csv") for filebase in filenames}
ages = [1] + list(range(5,61,5))

for col in ['Age', 'Cash', 'Shocks', 'ShockProb', 'FitnessSpending', 'Fitness', 'InsuranceSpending', 'InsurancePayout', 'BuyIns', 'TotalJoy']:
    print()
    print(col)
    for filebase in filenames:
        means = [(dfs[filebase].loc[dfs[filebase]['Age'] == age])[col].mean() for age in ages]
        print("{0:35}".format(filebase) + "  " + ' '.join(["{0:7.2f}".format(mean) for mean in means]) + " --- " + "{0:7.2f}".format(np.mean(means)))

        

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
