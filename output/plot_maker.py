#!/usr/bin/env python3

import numpy as np
import pandas as pd
from matplotlib.backends.backend_pdf import PdfPages
import matplotlib.pyplot as plt
import string
from collections import OrderedDict
import copy
import glob
import sys
import json
import os
from math import log2, floor
from pprint import pprint

# These can be changed easily
display_cols =  ['Cash', 'Shocks', 'ShockProb', 'AtMaxShocks', 'DieFrac', 'NextFitness',
                 'InsurancePaid','BuyIns', 'Enjoyment', 'TotalJoy',
                 'JoySpending', 'FitnessSpending', 'InsuranceSpending', 'NextCash']

# mult_dict and initials need to match those of config_writer.py
mult_dict = {'MaxShocks' : 1,
             'Size' : 1,
             'JoyJ' : 1,
             'JoyShift' : 100,
             'ProbCoeff': 100,
             'ProbRate' : 100,
             'ProbModJ' : 1,
             'ProbModMax' : 100,
             'FitDegen' : 100,
             'FitPrice' : 10,
             'JobIntercept': 1,
             'JobSlope' : 1,
             'Discount' : 100}

initials = {
    'MaxShocks' : 'ms',
    'Size' : 'ss',
    'JoyJ' : 'j',
    'JoyShift' : 'js',
    'ProbCoeff' : 'pc',
    'ProbRate' : 'pr',
    'ProbModJ' : 'pj',
    'ProbModMax' : 'pm',
    'FitDegen' : 'd',
    'FitPrice' : 'p',
    'JobIntercept' : 'i',
    'JobSlope' : 's',
    'Discount' : 'dc'}


#Everything below should be automated
init_dict = {v: k for k, v in initials.items()}

def parse_filename(filename):
    base_name = os.path.basename(filename)
    base_name = base_name.rsplit('.', 1)[0]
    val_strs = base_name.split("_")
    vals = OrderedDict()
    for short_name in val_strs:
        if short_name == 'jl':
            key = 'JoyMod'
            val = 'ShockLinear'
        elif short_name == 'jc':
            key = 'JoyMod'
            val = 'ShockCosine'
        elif short_name == 'emp':
            key = 'Ins'
            val = 'Fixed'
        elif short_name == 'act':
            key = 'Ins'
            val = 'Actuarial'
        else:
            inits = short_name.rstrip(string.digits)
            key = init_dict[inits]
            val_str = short_name.lstrip(string.ascii_letters)
            val = float(val_str) / mult_dict[key]
        vals[key] = (short_name, val)
    return vals

def to_file_name(keys, vals_dict):
    return '_'.join([vals_dict[key] for key in keys]) + '_rand_lives.csv'


def get_fixed_flex_keys(joint_vals):
    fixed = []
    flex = []
    for key in joint_vals:
        if len(set(joint_vals[key])) == 1:
            fixed.append(key)
        else:
            flex.append(key)
    return fixed, flex

# Only supports pairwise merging, not 3+ merge at a time
def get_merged_flex_keys(flex_keys, joint_vals):
    n = len(flex_keys)
    merged = []
    unmerged = flex_keys[:]
    n_flexes = [len(set(joint_vals[key])) for key in flex_keys]
    for i in range(n):
        for j in range(i + 1, n):
            joint_uniques = len(set(zip(joint_vals[flex_keys[i]], joint_vals[flex_keys[j]])))
            if joint_uniques != n_flexes[i] * n_flexes[j]:
               merged.append((flex_keys[i], flex_keys[j]))
               unmerged.remove(flex_keys[i])
               unmerged.remove(flex_keys[j])
    return merged + unmerged

if len(sys.argv) != 2:
    print("Error: expects exactly one argument")
    print("\plot_maker.py dir_name")
    exit

dir_name = sys.argv[1]
param_files = glob.glob(dir_name + "/*.json")
param_files.sort()
params = []
for f in param_files:
    params.append(parse_filename(f))


joint_vals = OrderedDict()
for key in params[0]:
    joint_vals[key] = [param[key] for param in params]

fixed_keys, flex_keys = get_fixed_flex_keys(joint_vals)
flex_keys = get_merged_flex_keys(flex_keys, joint_vals)

for key in fixed_keys:
    joint_vals[key] = [joint_vals[key][0]]
for key in flex_keys:
    if type(key) is tuple:
        joint = set(zip(*[joint_vals[k] for k in key]))
        for i in range(len(key)):
            joint_vals[key[i]] = [val[i] for val in joint]
    else:
        joint_vals[key] = list(set(joint_vals[key]))

tuple_vals = copy.deepcopy(joint_vals)
for key in flex_keys:
    if type(key) is tuple:
        zipped_vals = list(zip(*[joint_vals[k] for k in key]))
        tuple_vals[key] = zipped_vals
        for k in key:
            del tuple_vals[k]

for key in tuple_vals:
    tuple_vals[key] = sorted(tuple_vals[key])
for key in joint_vals:
    joint_vals[key] = sorted(joint_vals[key])

file_titles = list(joint_vals.keys())
titles = list(tuple_vals.keys())
keys = list(tuple_vals.keys())

def add_treats(treats, title, vals):
    new_treats = []
    if (type(vals) is not list):
        vals = [vals]
    for treat in treats:
        for v in vals:
            t = copy.deepcopy(treat)
            if type(title) is tuple:
                for i in range(len(title)):
                    t[title[i]] = v[i]
            else:
                t[title] = v
            new_treats.append(t)
    treats = new_treats
    return new_treats

def get_file_name(plot_set):
    name = {}
    i=88
    for title in titles:
        if type(title) is tuple:
            if type(plot_set[title]) is list:
                for key in title:
                    name[key] = chr(i)
                i += 1
            else:
                for i in range(len(title)):
                    name[title[i]] = plot_set[title][i][0]
        else:
            if type(plot_set[title]) is list:
                name[title] = chr(i)
                i += 1
            else:
                name[title] = plot_set[title][0]
    
    return '_'.join([name[key] for key in file_titles])

def get_legends(plot_set):
    legends = [[]]
    for t in titles:
        if type(plot_set[t]) is list:
            new_legends = []
            for leg in legends:
                for v in plot_set[t]:
                    new_leg = copy.deepcopy(leg)
                    if type(t) is tuple:
                        new_leg.append(str(t) + '=' + str(tuple(n[1] for n in v)))
                    else:
                        new_leg.append(str(t) + '=' + str(v[1]))
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
            treat_out.append(treat[t][0])
        out.append('_'.join(treat_out))
    return out

def get_fixed_title(plot_set):
    title = []
    for t in titles:
        if type(plot_set[t]) is not list:
            title.append(str(t) + '=' + str(plot_set[t][1]))
    return ', '.join(title)

def gen_all_poss(cur_set, fixed_keys):
    if not fixed_keys:
        return cur_set 
    new_set = []
    key = fixed_keys[0]
    for treat in cur_set:
        for val_set in tuple_vals[key]:
            new_treat = copy.deepcopy(treat)
            new_treat[key] = val_set
            new_set.append(new_treat)
    return gen_all_poss(new_set, fixed_keys[1:])

new_fixed_keys = []
for i in range(len(flex_keys)):
    all_keys = fixed_keys + flex_keys
    all_keys.remove(flex_keys[i])
    new_fixed_keys.append(all_keys)
fixed_keys = new_fixed_keys

flex_keys = [[key] for key in flex_keys]

plot_treats = []
for fixed, flex in zip(fixed_keys, flex_keys):
    fixed_treats = gen_all_poss([{}], fixed)
    flex_treats = {title : tuple_vals[title] for title in flex}
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

all_treatments = set()
for treats in treat_names:
    for t in treats:
        all_treatments.add(t)
all_treatments = list(all_treatments)

def get_file_means(filebase, condition_on_alive):
    df = pd.read_csv(dir_name + "/" + filebase + "_rand_lives.csv")
    if condition_on_alive:
        df = df.loc[df['AtMaxShocks'] == False]
    df = df.groupby(['Age'], as_index=False).mean()
    df.loc[df['Dies'] == 0, 'DieFrac'] = 0
    df.loc[df['Dies'] > 0, 'DieFrac'] = df['Dies'] / (1 - df['AtMaxShocks'] + df['Dies'])
    return df

for condition_on_alive in [True, False]:
    print("Reading Data..." + str(condition_on_alive))
    treatment_means = {treat : get_file_means(treat, condition_on_alive) for treat in all_treatments}
    print("Done!  Now processing...")

    colors=['blue', 'red', 'green', 'orange']
    ages = treatment_means[all_treatments[0]]['Age'].tolist()
    for data in metadata:
        treatments = data['Treatments']
        n_ins = len(treatments)
        ext = ''
        if condition_on_alive:
            ext = '_dd'
        with PdfPages(dir_name + "/" + data['Filename'] + ext + '.pdf') as pdf:
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
