#!/usr/bin/env python3

import json
import copy
import os
import sys
from collections import OrderedDict
import time

# Notes:
#   Instead of all combos, job intercepts and slopes are paired up.
#     i.e. intercepts = [0, 0, 1], slopes = [1, 2, 1]
#           => 3 job settings.  int/slope pairing =  [[0,1], [0,2], [1,1]]
#
#   Allowable 'Ins' values: ['Actuarial', 'Fixed']
#   Allowable 'JoyMod' values: ['ShockLinear', 'ShockCosine']
#   Order of parameters here will be reflected in file name
bases_dict = OrderedDict()
bases_dict['MaxShocks'] =    [6]
bases_dict['Size'] =         [200]
bases_dict['JoyJ'] =         [40]
bases_dict['JoyMod'] =       ['ShockLinear']
bases_dict['ProbCoeff'] =    [1.5, 2]
bases_dict['ProbRate'] =     [0.75]
bases_dict['ProbModJ'] =     [30, 40]
bases_dict['ProbModMax'] =   [1.00]
bases_dict['FitDegen'] =     [0.20]
bases_dict['FitPrice'] =     [3.0]
bases_dict['JobIntercept'] = [100]
bases_dict['JobSlope'] =     [0]
bases_dict['Discount'] =     [1.00]
bases_dict['Ins'] =          ['Actuarial']


# Note: Changing these parameters will not show up in file name
actuarial_scale = 1
actuarial_admin_cost = 0

base_age_coeff = 0.025 #0.09
base_age_rate = 0.02   #0.027465
base_shock_coeff = 0.1 #0.045
base_shock_rate = 0.35 #0.27

max_age = 30
max_fitness = 100
min_debt_payment = 1
shock_count_per_shock = 1
joy_max_mod = 1
employer_premium_frac = 1/4

def employer_total_price_estimate(shock_size):
    return (2/15 * shock_size) + 3

def get_max_savings(shock_size):
    return 0 #int(shock_size/5)





#### Shouldn't need to change anything below here for basic parameter file making ####
def main():
    if len(sys.argv) != 2:
        print("Error: expects exactly one argument")
        print("\twrite_configs.py dir_name")
        exit()

    dir_name = sys.argv[1]
    out = init_out()
    dicts = create_parameter_sets(out)
    write_files(dir_name, dicts)

def init_out():
    out = {}
    out['treatments'] = {}
    out['max_age'] = max_age
    out['max_fitness'] = max_fitness
    out['min_debt_payment'] = min_debt_payment
    out['shock_count_size'] = shock_count_per_shock
    out['job'] = {
        'type' : 'AgeLinear'
    }
    out['joy'] = {
        'type' : 'Fractional',
        'mod' : {
            'max_modulation' : joy_max_mod
        }
    }
    out['probability'] = {
        'type' : 'GompertzShocks'
    }
    out['probability']['mod'] = {
        'type' : 'FitnessFractional'
    }
    out['fitnesses'] = [{'type' : 'ProportionalLoss'}, {'type' : 'FixedPrice'}]
    return out


def add_options(dicts, titles, option_names, parent = '', sub_parent = ''): 
    new_dicts = []
    for cur_out in dicts:
        if type(titles) != list:
            titles = [titles]
        if type(option_names) != list:
            option_names = [option_names]
        value_sets = [bases_dict[title] for title in titles]
        for value_set in zip(*value_sets):
            out2 = copy.deepcopy(cur_out)
            for title, option_name, value in zip(titles, option_names, value_set):
                if parent:
                    if sub_parent != '':
                        out2[parent][sub_parent][option_name] = value                    
                    else:
                        out2[parent][option_name] = value
                else:
                    out2[option_name] = value
                out2['treatments'][title] = value
            new_dicts.append(out2)
    return new_dicts


def add_ins_options(dicts):
    new_dicts = []
    title = 'Ins'
    for cur_out in dicts:
        for ins in bases_dict[title]:
            out2 = copy.deepcopy(cur_out)
            out2['insurance'] = {
                'type' : ins
            }
            if ins == 'Actuarial':
                out2['insurance']['scale'] = actuarial_scale
                out2['insurance']['admin_cost'] = actuarial_admin_cost
            else:
                out2['insurance']['premium'] = int(employer_total_price_estimate(out2['treatments']['Size']) * employer_premium_frac)

            out2['treatments'][title] = ins
            new_dicts.append(out2)
    return new_dicts

def create_parameter_sets(out):
    dicts = [out]
    dicts = add_options(dicts, 'MaxShocks', 'max_shocks')
    dicts = add_options(dicts, 'Size', 'shock_income_size')
    dicts = add_options(dicts, 'JoyJ', 'j', 'joy')
    dicts = add_options(dicts, 'JoyMod', 'type', 'joy', 'mod')
    dicts = add_options(dicts, 'ProbCoeff', 'age_coeff', 'probability')
    dicts = add_options(dicts, 'ProbCoeff', 'shock_coeff', 'probability')
    dicts = add_options(dicts, 'ProbRate', 'age_rate', 'probability')
    dicts = add_options(dicts, 'ProbRate', 'shock_rate', 'probability')
    dicts = add_options(dicts, 'ProbModMax', 'max_modulation', 'probability', 'mod')
    dicts = add_options(dicts, 'ProbModJ', 'j', 'probability', 'mod')
    dicts = add_options(dicts, 'FitDegen', 'rate', 'fitnesses', 0)
    dicts = add_options(dicts, 'FitPrice', 'price', 'fitnesses', 1)
    dicts = add_options(dicts, ['JobIntercept','JobSlope'], ['intercept','slope'], 'job')
    dicts = add_options(dicts, 'Discount', 'discount')
    dicts = add_ins_options(dicts)
    for s in dicts:
        s['probability']['age_coeff'] *= base_age_coeff
        s['probability']['age_rate'] *= base_age_rate
        s['probability']['shock_coeff'] *= base_shock_coeff
        s['probability']['shock_rate'] *= base_shock_rate
    for s in dicts:
        s['max_savings'] = get_max_savings(s['shock_income_size'])
        s['min_savings'] = -int(1.5 * s['shock_income_size'])
        if s['insurance']['type'] == 'Fixed':
            s['job']['intercept'] = s['job']['intercept'] - employer_total_price_estimate(s['shock_income_size'] * (1 - employer_premium_frac))
    return dicts

initials = {
    'MaxShocks' : 'ms',
    'Size' : 'ss',
    'JoyJ' : 'j',
    'JoyMod' : 'j',
    'ProbCoeff' : 'pc',
    'ProbRate' : 'pr',
    'ProbModJ' : 'pj',
    'ProbModMax' : 'pm',
    'FitDegen' : 'd',
    'FitPrice' : 'p',
    'JobIntercept' : 'i',
    'JobSlope' : 's',
    'Discount' : 'dc',
    'Ins' : ''}

mult_dict = {'MaxShocks' : 1,
             'Size' : 1,
             'JoyJ' : 1,
             'ProbCoeff': 100,
             'ProbRate' : 100,
             'ProbModJ' : 1,
             'ProbModMax' : 100,
             'FitDegen' : 100,
             'FitPrice' : 10,
             'JobIntercept': 1,
             'JobSlope' : 1,
             'Discount' : 100}

def get_value_string(name, val):
    if name == 'Ins':
        return {'Actuarial' : 'act', 'Fixed': 'emp'}[val]
    elif name == 'JoyMod':
        return {'ShockLinear' : 'l', 'ShockCosine' : 'c'}[val]
    else:
        multiplier = mult_dict[name]
        return str(int(val * multiplier))

def to_name(name, val):
    return initials[name] + get_value_string(name, val)

def write_files(dir_name, dicts):
    timestr = time.strftime("%m%d%y_%H%M%S")
    unique_dir_name = dir_name + "_" + timestr
    os.mkdir(unique_dir_name)
    for out in dicts:
        inits = []
        for key,val in out['treatments'].items():
            inits.append(to_name(key, val))
        with open(unique_dir_name + '/' + '_'.join(inits) + '.json', 'w') as outfile:
            json.dump(out, outfile, indent=4)

if __name__ == "__main__":
    main()
