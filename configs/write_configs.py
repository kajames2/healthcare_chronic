import json
import copy


max_shocks = ['ms6']
max_shocks_bases = [6]

size = ['ss200']# 'ss200', 'ss250','ss300'
size_bases = [200]# 200,250,300

joy_j = ['j40']
joy_j_bases = [40]

joy_mod = ['jl']
joy_mod_bases = ['ShockLinear']

prob_coeff = ['pc75']
prob_coeff_bases = [0.75]

prob_coeff = ['pc150', 'pc200']#, 'pc300', 'pc350']
prob_coeff_bases = [1.5, 2]#, 3.0, 3.5]

prob_rate = ['pr75']
prob_rate_bases = [0.75]

prob_mod_j = ['pj30']
prob_mod_j_bases = [30]

prob_mod_max = ['pm100']
prob_mod_max_bases = [1.00]

#fit_degen = ['d18']
#fit_degen_bases = [0.18]

fit_degen = ['d20']
fit_degen_bases = [0.20]

fit_price = ['p30', 'p10000']
fit_price_bases = [3.0, 1000.0]

#fit_price = ['p10000']
#fit_price_bases = [1000.0]

discounts = ['dc100']
discounts_bases = [1.00]

insures = ['act']
insures_bases = ['Actuarial']

#insures = ['act', 'emp']
#insures_bases = ['Actuarial', 'Fixed']

# Note: intercepts and slopes are paired up.
#job_intercept = ['i100','i40', 'i82']
#job_intercept_bases = [100, 40, 82]
#job_slope = ['s0', 's4', 's0']
#job_slope_bases = [0, 4, 0]

job_intercept = ['i100']
job_intercept_bases = [100]
job_slope = ['s0']
job_slope_bases = [0]

actuarial_scale = 1
actuarial_admin_cost = 0

def est_emp_insurance_price(shock_size):
    return (2/15 * shock_size) + 3

#max_shocks = ['ms4', 'ms6', 'ms8']
#max_shocks_bases = [4, 6, 8]

#size = ['ss250', 'ss300', 'ss350']
#size_bases = [250, 300, 350]

#joy_j = ['j30', 'j40', 'j50']
#joy_j_bases = [30, 40, 50]

#joy_mod = ['jl', 'jc']
#joy_mod_bases = ['ShockLinear', 'ShockCosine']

#prob_coeff = ['pc60', 'pc70', 'pc80']
#prob_coeff_bases = [0.60, 0.70, 0.80]

#prob_rate = ['pr40', 'pr70', 'pr100']
#prob_rate_bases = [0.40, 0.70, 1.00]

#prob_mod_j = ['pj20', 'pj30', 'pj40']
#prob_mod_j_bases = [20, 30, 40]

#prob_mod_max = ['pm50', 'pm75', 'pm100']
#prob_mod_max_bases = [0.50, 0.75, 1.00]

#fit_degen = ['d15','d18','d20']
#fit_degen_bases = [0.15, 0.18, 0.20]

#fit_price = ['p20','p30','p40']
#fit_price_bases = [2.0, 3.0, 4.0]

#discounts = ['dc70', 'dc80', 'dc90', 'dc100']
#discounts_bases = [0.70, 0.80, 0.90, 1.00]

#insures = ['emp', 'act']
#insures_bases = ['Fixed', 'Actuarial']

all_options = [max_shocks, size, joy_j, joy_mod, prob_coeff,
               prob_rate, prob_mod_j, prob_mod_max, fit_degen, fit_price, job_intercept, job_slope, discounts, insures]

all_bases = [max_shocks_bases, size_bases, joy_j_bases, joy_mod_bases, prob_coeff_bases,
             prob_rate_bases, prob_mod_j_bases, prob_mod_max_bases, fit_degen_bases, fit_price_bases, job_intercept_bases, job_slope_bases, discounts_bases, insures_bases]

titles = ['MaxShocks', 'Size', 'JoyJ', 'JoyMod', 'ProbCoeff', 'ProbRate', 'ProbModJ', 'ProbModMax', 'FitDegen', 'FitPrice', 'JobIntercept', 'JobSlope', 'Discount', 'Ins']
options_dict  = dict(zip(titles, all_options))
bases_dict = dict(zip(titles, all_bases))

options_bases_dict = {key : dict(zip(options_dict[key], bases_dict[key])) for key in titles}

bases_options_dict = {key : dict(zip(bases_dict[key], options_dict[key])) for key in titles}

out = {}
out['treatments'] = {}
out['max_age'] = 30
out['max_fitness'] = 100
out['min_debt_payment'] = 1
out['shock_count_size'] = 1

out['job'] = {
    'type' : 'AgeLinear'
}

out['joy'] = {
    'type' : 'Fractional',
    'mod' : {
        'max_modulation' : 1
    }
}

out['probability'] = {
    'type' : 'GompertzShocks'
}

out['probability']['mod'] = {
    'type' : 'FitnessFractional'
}

out['fitnesses'] = [{'type' : 'ProportionalLoss'}, {'type' : 'FixedPrice'}]

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
                out2['insurance']['premium'] = int(est_emp_insurance_price(out2['treatments']['Size'])/4)

            out2['treatments'][title] = ins
            new_dicts.append(out2)
    return new_dicts

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
#    s['probability']['age_coeff'] *= 0.09
    s['probability']['age_coeff'] *= 0.025
#    s['probability']['age_rate'] *= 0.027465
    s['probability']['age_rate'] *= 0.02
#    s['probability']['shock_coeff'] *= 0.045
    s['probability']['shock_coeff'] *= 0.1
#    s['probability']['shock_rate'] *= 0.27
    s['probability']['shock_rate'] *= 0.35

for s in dicts:
    s['max_savings'] = 0 #int(s['shock_income_size']/5)
    s['min_savings'] = -int(1.5 * s['shock_income_size'])
    if s['insurance']['type'] == 'Fixed':
        s['job']['intercept'] = s['job']['intercept'] - est_emp_insurance_price(s['shock_income_size'] * 3/4)


for out in dicts:
    options = [bases_options_dict[t][v] for t,v in out['treatments'].items()]
    with open('_'.join(options) + '.json', 'w') as outfile:
        json.dump(out, outfile, indent=4)
