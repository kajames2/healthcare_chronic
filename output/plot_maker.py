import numpy as np
import pandas as pd
from matplotlib.backends.backend_pdf import PdfPages
import matplotlib.pyplot as plt
import copy


### THE STUFF BELOW NEEDS TO BE UPDATED ACCORDING TO THE FILES RAN ###


max_shocks = ['ms6']
size = ['ss200']# 'ss200', 'ss250', 'ss300'
joy_j = ['j40']
joy_mod = ['jl']
#prob_coeff = ['pc75']
prob_coeff = ['pc150', 'pc200']#, 'pc300', 'pc350']
prob_rate = ['pr75']
prob_mod_max = ['pm100']
prob_mod_j = ['pj30']
#fit_degen = ['d18']
fit_degen = ['d20']
fit_price = ['p30', 'p10000']
discount = ['dc100']#, 'dc90','dc85', 'dc80']
ins = ['act']#, 'emp']

# Note: intercepts and slopes are paired up.
#job_intercept = ['i40', 'i100', 'i82']
#job_slope = ['s4', 's0', 's0']

job_intercept = ['i100']
job_slope = ['s0']


#max_shocks = ['ms4', 'ms6', 'ms8']
#size = ['ss250', 'ss300', 'ss350']
#joy_j = ['j20', 'j30', 'j40', 'j50']
#joy_mod = ['jl', 'jc']
#prob_coeff = ['pc60', 'pc70', 'pc80']
#prob_rate = ['pr40', 'pr70', 'pr100']
#prob_mod_max = ['pm50', 'pm75', 'pm100']
#prob_mod_j = ['pj20', 'pj30', 'pj40']
#fit_degen = ['d15','d18','d20']
#fit_price = ['p20','p30','p40']
#discount = ['dc70', 'dc80', 'dc90', 'dc100']

all_short = [ins, max_shocks, size, joy_j, joy_mod, prob_coeff, prob_rate, prob_mod_max, prob_mod_j, fit_degen, fit_price, list(zip(job_intercept, job_slope)), discount]

# Needs better name.  Order of graphs.  Ins assumed to always be first.  Order doesn't really matter after that, as long as it's consistent with the above.
titles = [ 'Ins', 'MaxShocks', 'ShockSize', 'JoyJ', 'JoyMod', 'ProbCoeff', 'ProbRate', 'ProbModMax', 'ProbModJ', 'FitDegen', 'FitPrice', ('JobIntercept', 'JobSlope'), 'Discount']

# Order of parameters in the filenames
file_titles = ['MaxShocks', 'ShockSize', 'JoyJ', 'JoyMod', 'ProbCoeff', 'ProbRate', 'ProbModMax', 'ProbModJ', 'FitDegen', 'FitPrice', ('JobIntercept', 'JobSlope'), 'Discount', 'Ins']

### EVERYTHING BELOW HERE SHOULD BE OKAY ###

short_dict = dict(zip(titles, all_short))

keys = list(short_dict.keys())

def add_treats(treats, title, vals):
    new_treats = []
    if (type(vals) is not list):
        vals = [vals]
    for treat in treats:
        for v in vals:
            t = copy.deepcopy(treat)
            t[title] = v
            new_treats.append(t)
    treats = new_treats
    return new_treats

def get_file_name(plot_set):
    name = []
    for title in file_titles:
        if type(plot_set[title]) is str:
            name.append(plot_set[title])
        elif type(plot_set[title]) is tuple:
            for t in plot_set[title]:
                name.append(t)
        else:
            name.append('X')
    return '_'.join(name)
    
def get_legends(plot_set):
    legends = [[]]
    for t in titles:
        if type(plot_set[t]) is list:
            new_legends = []
            for leg in legends:
                for v in plot_set[t]:
                    new_leg = copy.deepcopy(leg)
                    new_leg.append(str(t) + '=' + str(v))
                    new_legends.append(new_leg)
            legends = new_legends
    legends = ['+'.join(leg) for leg in legends]
    return legends
    
def get_treatment_names(plot_set):
    treats = [{}]
    for title in titles:
        treats = add_treats(treats, title, plot_set[title])
    out = []
    for treat in treats:
        treat_out = []
        for t in file_titles:
            if type(treat[t]) == tuple:
                for val in treat[t]:
                    treat_out.append(val)
            else:
                treat_out.append(treat[t])
        out.append('_'.join(treat_out))
    return out

def get_fixed_title(plot_set):
    title = []
    for t in titles:
        if type(plot_set[t]) is not list:
            title.append(str(t) + '=' + str(plot_set[t]))
    return ', '.join(title)


def gen_all_poss(cur_set, fixed_keys):
    if not fixed_keys:
        return cur_set 
    new_set = []
    key = fixed_keys[0]
    for treat in cur_set:
        for val_set in short_dict[key]:
            new_treat = copy.deepcopy(treat)
            new_treat[key] = val_set
            new_set.append(new_treat)
    return gen_all_poss(new_set, fixed_keys[1:])
    
keys = list(short_dict.keys())
fixed_keys = []
flex_keys = []
for key in keys:
    if len(short_dict[key]) > 1:
        fixed = keys[:]
        fixed.remove(key)
        fixed_keys.append(fixed)
        flex_keys.append([key])

plot_treats = []
for fixed, flex in zip(fixed_keys, flex_keys):
    fixed_treats = gen_all_poss([{}], fixed)
    flex_treats = {title : short_dict[title] for title in flex}
    for treat in fixed_treats:
        treat.update(flex_treats)
    plot_treats = plot_treats + fixed_treats

treat_names = [get_treatment_names(t) for t in plot_treats]
fixed_titles = [get_fixed_title(t) for t in plot_treats]
file_names = [get_file_name(t) for t in plot_treats]
print(file_names)
legends = [get_legends(t) for t in plot_treats]

metadata = []
for (name, title, filename, legends) in zip(treat_names, fixed_titles, file_names, legends):
    metadata.append({'Treatments' : name,
                     'Title' : title,
                     'Filename' : filename,
                     'Legends' : legends})

ages = range(1,31)

all_treatments = set()
for treats in treat_names:
    for t in treats:
        all_treatments.add(t)
all_treatments = list(all_treatments)

def get_file_means(filebase):
    df = pd.read_csv(filebase + "_rand_lives.csv")
    df = df.groupby(['Age'], as_index=False).mean()
    return df

print("Reading Data...")
treatment_means = {treat : get_file_means(treat) for treat in all_treatments}
print("Done!  Now processing...")

display_cols =  ['Cash', 'Shocks', 'ShockProb', 'AtMaxShocks', 'NextFitness',
                 'InsurancePaid','BuyIns', 'Enjoyment', 'TotalJoy',
                 'JoySpending', 'FitnessSpending', 'InsuranceSpending', 'NextCash']

colors=['blue', 'red', 'green', 'orange']
ages = treatment_means[all_treatments[0]]['Age'].tolist()
for data in metadata:
    treatments = data['Treatments']
    n_ins = len(treatments)
    with PdfPages(data['Filename'] + '.pdf') as pdf:
        for col in display_cols:
            plt.figure(figsize=(6, 6))
            for i in range(len(treatments)):
                if i >= n_ins:
                    plt.plot(ages, treatment_means[treatments[i]][col].tolist(), '--', linewidth=2, color=colors[i-n_ins], label=data['Legends'][i])
                else:
                    plt.plot(ages, treatment_means[treatments[i]][col].tolist(), linewidth=2, color=colors[i], label=data['Legends'][i])
            plt.title(col)
            plt.legend()
            pdf.savefig()
            plt.close()
        d = pdf.infodict()
        d['Title'] = data['Title']
