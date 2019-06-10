import numpy as np
import pandas as pd
from matplotlib.backends.backend_pdf import PdfPages
import matplotlib.pyplot as plt
import copy


### THE STUFF BELOW NEEDS TO BE UPDATED ACCORDING TO THE FILES RAN ###

max_shocks_short = ['ms6']
max_shocks = ['6']

size_short = ['s105']
size = ['105']

alpha_short = ['a020']
alpha = ['0.20']

beta_short = ['b025']
beta = ['0.025']

eta_short = ['e80']
eta = ['0.80']

gamma_c_short = ['gc8']
gamma_c = ['8']

gamma_h_short = ['gh8']
gamma_h = ['8']

fit_degen_short = ['d15']
fit_degen = ['0.15']

fit_price_short = ['fp6']
fit_price = ['6.0']

fitness_r_short = []
fitness_r = []

lambda_h_short = []
lambda_h = []

mu_h = []
mu_h_bases = []

p_short = []
p = []

k_short = []
k = []

c_short = []
c = []



discount_short = ['d100']
discount = ['1.00']

insures_short = ['act', 'emp']
insures = ['Act', 'Emp']

#######################################
# un/mute everything between bands 

fitness_r_short = ['fr1.0',]
fitness_r = ['fit_r=1.0']

lambda_h_short = ['lam10']
lambda_h = ['10']

mu_h_short = ['mu1']
mu_h = ['1.0']

health_model_short = ['steve']
health_model = ['HealthDependentSteve']

#health_model_short = ['steve', 'dustin']
#health_model = ['HealthDependentSteve', 'HealthDependentDustin']

#####################################
# mute or unmute not whatever was done above

#p_short = ['p1']
#p = ['1']

#k_short = ['k.5']
#k = ['0.5']

#c_short = ['c2']
#c = ['2']

#health_model_short = ['fan']
#health_model = ['HealthDependentFan']

#########################################


#max_shocks_short = ['ms6', 'ms8']
#max_shocks = ['6', '8']

#size_short = ['s75', 's90', 's105']
#size = ['75', '90', '105']

#alpha_short = ['a10', 'a125', 'a15']
#alpha = ['0.10', '0.125', '0.15']

#beta_short = ['b02', 'b03', 'b04', 'b05']
#beta = ['0.02', '0.03', '0.04', '0.05']

#discount_short = ['d80', 'd90', 'd100']
#discount = ['0.80', '0.90', '1.00']

#eta_short = ['e0.6', 'e0.7']
#eta = ['0.6', '0.7']

#gamma_c_short = ['gc5', 'gc10']
#gamma_c = ['5', '10']

#gamma_h_short = ['gh10', 'gh20']
#gamma_h = ['10', '20']

#fit_degen_short = ['d15','d20','d25']
#fit_degen = ['0.15', '0.20', '0.25']

#fit_price_short = ['p500', 'p600']
#fit_price = ['5', '6']

#insures_short = ['act']
#insures = ['Act']





all_longs = [insures, max_shocks, size, alpha, beta, eta, gamma_c, gamma_h, fit_degen, fit_price, discount, fitness_r, lambda_h, mu_h, p, k, c, health_model]

all_shorts = [insures_short, max_shocks_short, size_short, alpha_short, beta_short, eta_short, gamma_c_short, gamma_h_short, fit_degen_short, fit_price_short, discount_short, fitness_r_short, lambda_h_short, mu_h_short, p_short, k_short, c_short, health_model_short]


# Needs better name.  Order of graphs.  Ins assumed to always be first.  Order doesn't really matter after that, as long as it's consistent with the above.
titles = ['Ins', 'MaxShocks', 'ShockSize', 'Alpha', 'Beta', 'Eta', 'GammaC', 'GammaH', 'DegenRate', 'FitPrice', 'Discount', 'FitR', 'Lambda', 'Mu', 'P','K','C','HealthFunc']

# Order of parameters in the filenames
file_titles = ['MaxShocks', 'ShockSize', 'GammaC', 'GammaH', 'Alpha', 'Beta', 'Eta', 'DegenRate', 'FitPrice', 'Discount', 'FitR', 'Lambda', 'Mu', 'P','K','C','HealthFunc', 'Ins']

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
        if not long_dict[title]:
            continue
        if type(plot_set[title]) is str:
            name.append(plot_set[title])
        else:
            name.append('X')
    return '_'.join(name)
    
def get_legends(plot_set):
    legends = [[]]
    for t in titles:
        if not long_dict[t]:
            continue
        if type(plot_set[t]) is not str:
            new_legends = []
            for leg in legends:
                for v in plot_set[t]:
                    new_leg = copy.deepcopy(leg)
                    new_leg.append(t + "=" + short_long_dict[t][v])
                    new_legends.append(new_leg)
            legends = new_legends
    legends = ['+'.join(leg) for leg in legends]
    return legends
    
def get_treatment_names(plot_set):
    treats = [{}]
    for title in titles:
        if not long_dict[title]:
            continue
        treats = add_treats(treats, title, plot_set[title])

    out = []
    for treat in treats:
        treat_out = []
        for t in file_titles:
            if not long_dict[t]:
                continue
            treat_out.append(treat[t])
        out.append('_'.join(treat_out))
    return out

def get_fixed_title(plot_set):
    title = []
    for t in titles:
        if not long_dict[t]:
            continue
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
fixed_keys = []
flex_keys = []
for key in keys:
    if len(short_dict[key]) > 1:
        fixed = keys[:]
        fixed.remove(key)
        fixed = [fix for fix in fixed if long_dict[fix]]
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
