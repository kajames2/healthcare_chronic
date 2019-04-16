import json
import copy


max_shocks = ['ms6']
size = ['s150']
p_mid = ['pm15']
delta_t = ['dt10']
delta_h = ['dh10']
gamma_c = ['gc30']
gamma_h = ['gh10']
fit_degen = ['d15']
fit_price = ['p30']
discount = ['d100']
insures = ['act']

max_shocks_bases = [6]
size_bases = [150]
p_mid_bases = [0.15]
delta_t_bases = [0.1]
delta_h_bases = [0.1]
gamma_c_bases = [30]
gamma_h_bases = [10]
fit_degen_bases = [0.15]
fit_price_bases = [3.0]
discount_bases = [1.00]
insures_bases = ['Actuarial']

#max_shocks = ['ms6']
#max_shocks_bases = [6]

#size = ['s250', 's400']
#size_bases = [250, 400]

#p_mid = ['pm05', 'pm15', 'pm25']
#p_mid_bases = [0.05, 0.15, 0.25]

#delta_t = ['dt05', 'dt10', 'dt15']
#delta_t_bases = [0.05, 0.1, 0.15]

#delta_h = ['dh05', 'dh10', 'dh15']
#delta_h_bases = [0.05, 0.1, 0.15]

#gamma_c = ['gc20', 'gc30', 'gc40']
#gamma_c_bases = [20, 30, 40]

gamma_h = ['gh10', 'gh20', 'gh30']
gamma_h_bases = [10, 20, 30]

#fit_degen = ['d15','d20','d25']
#fit_degen_bases = [0.15, 0.20, 0.25]

#fit_price = ['p20','p30','p40']
#fit_price_bases = [2.0, 3.0, 4.0]

insures = ['emp', 'act']
insures_bases = ['Fixed', 'Actuarial']


all_options = [max_shocks, size, p_mid, delta_t, delta_h, gamma_c, gamma_h, fit_degen, fit_price, discount, insures]
all_bases = [max_shocks_bases, size_bases, p_mid_bases, delta_t_bases, delta_h_bases, gamma_c_bases, gamma_h_bases, fit_degen_bases, fit_price_bases, discount_bases, insures_bases]
titles = ['NShocks', 'Size', 'ProbMid', 'DeltaT', 'DeltaH', 'GammaC', 'GammaH', 'FitDegen', 'FitPrice', 'Discount', 'Ins']
options_dict  = dict(zip(titles, all_options))
bases_dict = dict(zip(titles, all_bases))

options_bases_dict = {key : dict(zip(options_dict[key], bases_dict[key])) for key in titles}
bases_options_dict = {key : dict(zip(bases_dict[key], options_dict[key])) for key in titles}

out = {}
out['treatments'] = {}
out['max_age'] = 30
out['max_fitness'] = 60
out['min_debt_payment'] = 1
out['shock_count_size'] = 1
out['fitnesses'] = []

out['joy'] = {
    'type' : 'HealthDependent'
}

out['probability'] = {
    'type' : 'HealthDependent',
    'eta' : 2
}

out['fitnesses'] = [{'type' : 'ProportionalLoss'}, {'type' : 'FixedPrice'}]

def add_options(dicts, title, option_name, parent = '', sub_parent = ''): 
    new_dicts = []
    for cur_out in dicts:
        for value in bases_dict[title]:
            out2 = copy.deepcopy(cur_out)
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
                out2['insurance']['scale'] = 1
            else:
                out2['insurance']['premium'] = int(5 * (out2['treatments']['Size']/200.))

            out2['treatments'][title] = ins
            new_dicts.append(out2)
    return new_dicts


dicts = [out]
dicts = add_options(dicts, 'NShocks', 'max_shocks')
dicts = add_options(dicts, 'Size', 'shock_income_size')
dicts = add_options(dicts, 'GammaC', 'gamma_consumption', 'joy')
dicts = add_options(dicts, 'GammaH', 'gamma_health', 'joy')
dicts = add_options(dicts, 'DeltaT', 'delta_age', 'probability')
dicts = add_options(dicts, 'DeltaH', 'delta_health', 'probability')
dicts = add_options(dicts, 'ProbMid', 'midlife_prob', 'probability')
dicts = add_options(dicts, 'FitDegen', 'rate', 'fitnesses', 0)
dicts = add_options(dicts, 'FitPrice', 'price', 'fitnesses', 1)
dicts = add_options(dicts, 'Discount', 'discount')
dicts = add_ins_options(dicts)

for s in dicts:
    s['max_savings'] = int(s['shock_income_size']/3)
    s['min_savings'] = -int(2 * s['shock_income_size'])
    penalty = 0
    if s['insurance']['type'] == 'Fixed':
        penalty = s['insurance']['premium'] * 3
    s['job'] = {
        'type' : 'AgeLinear',
        'intercept' : 60 - penalty,
        'slope' : 0
    }

for out in dicts:
    options = [bases_options_dict[t][v] for t,v in out['treatments'].items()]
    with open('_'.join(options) + '.json', 'w') as outfile:
        json.dump(out, outfile, indent=4)
