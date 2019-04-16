import numpy as np
import pandas as pd
from matplotlib.backends.backend_pdf import PdfPages
import matplotlib.pyplot as plt
import copy


### THE STUFF BELOW NEEDS TO BE UPDATED ACCORDING TO THE FILES RAN ###


max_shocks = ['smax=6']
max_shocks_short = ['ms6']

size = ['shock=300']
size_short = ['ss300']

joy_j = ['j=40']
joy_j_short = ['j40']

joy_mod = ['joymod=Linear']
joy_mod_short = ['jl']

prob_coeff = ['probcoeff=0.75']
prob_coeff_short = ['pc75']

prob_rate = ['probrate=0.75']
prob_rate_short = ['pr75']

prob_mod_max = ['fitmaxeff=1.00']
prob_mod_max_short = ['pm100']

prob_mod_j = ['probj=30']
prob_mod_j_short = ['pj30']

fit_degen = ['fitdegen=0.18']
fit_degen_short = ['d18']

fit_price = ['fitprice=3.0']
fit_price_short = ['p30']

discount = ['disc=1.00']#, 'disc=0.90', 'disc=0.80']
discount_short = ['dc100']#, 'dc90', 'dc80']

ins = ['Actuarial', 'Employer']
ins_short = ['act', 'emp']

#max_shocks_short = ['ms4', 'ms6', 'ms8']
#max_shocks = ['smax=4', 'smax=6', 'smax=8']

#size_short = ['ss250', 'ss300', 'ss350']
#size = ['shock=250', 'shock=300', 'shock=350']

#joy_j_short = ['j20', 'j30', 'j40', 'j50']
#joy_j = ['j=20', 'j=30', 'j=40', 'j=50']

#joy_mod_short = ['jl', 'jc']
#joy_mod = ['joymod=ShockLinear', 'joymod=ShockCosine']

#prob_coeff_short = ['pc60', 'pc70', 'pc80']
#prob_coeff = ['probcoeff=0.60', 'probcoeff=0.70', 'probcoeff=0.80']

#prob_rate_short = ['pr40', 'pr70', 'pr100']
#prob_rate = ['probrate=0.40', 'probrate=0.70', 'probrate=1.00']

#prob_mod_max_short = ['pm50', 'pm75', 'pm100']
#prob_mod_max = ['fitmaxeff=0.50', 'fitmaxeff=0.75', 'fitmaxeff=1.00']

#prob_mod_j_short = ['pj20', 'pj30', 'pj40']
#prob_mod_j = ['probj=20', 'probj=30', 'probj=40']

#fit_degen_short = ['d15','d18','d20']
#fit_degen = ['fitdegen=0.15', 'fitdegen=0.18', 'fitdegen=0.20']

#fit_price_short = ['p20','p30','p40']
#fit_price = ['fitprice=2.0', 'fitprice=3.0', 'fitprice=4.0']

#discount_short = ['dc70', 'dc80', 'dc90', 'dc100']
#discount = ['disc=0.70', 'disc=0.80', 'disc=0.90', 'disc=1.00']


all_longs = [ins, max_shocks, size, joy_j, joy_mod, prob_coeff, prob_rate, prob_mod_max, prob_mod_j, fit_degen, fit_price, discount]

all_shorts = [ins_short, max_shocks_short, size_short, joy_j_short, joy_mod_short, prob_coeff_short, prob_rate_short, prob_mod_max_short, prob_mod_j_short, fit_degen_short, fit_price_short, discount_short]


# Needs better name.  Order of graphs.  Ins assumed to always be first.  Order doesn't really matter after that, as long as it's consistent with the above.
titles = [ 'Ins', 'MaxShocks', 'ShockSize', 'JoyJ', 'JoyMod', 'ProbCoeff', 'ProbRate', 'ProbModMax', 'ProbModJ', 'FitDegen', 'FitPrice', 'Discount']

# Order of parameters in the filenames
file_titles = ['MaxShocks', 'ShockSize', 'JoyJ', 'JoyMod', 'ProbCoeff', 'ProbRate', 'ProbModMax', 'ProbModJ', 'FitDegen', 'FitPrice', 'Discount', 'Ins']

### EVERYTHING BELOW HERE SHOULD BE OKAY ###


long_dict = dict(zip(titles, all_longs))
short_dict = dict(zip(titles, all_shorts))

keys = list(long_dict.keys())
long_short_dict = {key : dict(zip(long_dict[key], short_dict[key])) for key in keys}
short_long_dict = {key : dict(zip(short_dict[key], long_dict[key])) for key in keys}

def add_treats(treats, title, vals):
    new_treats = []
    if (type(vals) is str):
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
        else:
            name.append('X')
    return '_'.join(name)
    
def get_legends(plot_set):
    legends = [[]]
    for t in titles:
        if type(plot_set[t]) is not str:
            new_legends = []
            for leg in legends:
                for v in plot_set[t]:
                    new_leg = copy.deepcopy(leg)
                    new_leg.append(short_long_dict[t][v])
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
            treat_out.append(treat[t])
        out.append('_'.join(treat_out))
    return out

def get_fixed_title(plot_set):
    title = []
    for t in titles:
        if type(plot_set[t]) is str:
            title.append(t + '=' + short_long_dict[t][plot_set[t]])
    return ', '.join(title)


def gen_all_poss(cur_set, fixed_keys):
    if not fixed_keys:
        return cur_set 
    new_set = []
    key = fixed_keys[0]
    for treat in cur_set:
        for val in short_dict[key]:
            new_treat = copy.deepcopy(treat)
            new_treat[key] = val
            new_set.append(new_treat)
    return gen_all_poss(new_set, fixed_keys[1:])
    
keys = list(long_dict.keys())
#keys.remove('Ins')
fixed_keys = []
flex_keys = []
for key in keys:
    if len(short_dict[key]) > 1:
        fixed = keys[:]
        fixed.remove(key)
        fixed_keys.append(fixed)
        flex_keys.append([key])
#        flex_keys.append(['Ins', key])

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
    n_ins = int(len(treatments)/2)
    #n_ins = len(treatments)
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
