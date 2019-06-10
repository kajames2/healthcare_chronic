import json
import copy

max_shocks = ['ms6']
max_shocks_bases = [6]

size = ['s50']
size_bases = [50]

alpha = ['a020']
alpha_bases = [0.20]

beta = ['b025']
beta_bases = [0.025]

eta = ['e80']
eta_bases = [0.80]

gamma_c = ['gc8']
gamma_c_bases = [8]

gamma_h = ['gh8']
gamma_h_bases = [8]

fit_degen = ['d15']
fit_degen_bases = [0.15]

fit_price = ['fp6']
fit_price_bases = [6.0]

fitness_r = []
fitness_r_bases = []

lambda_h = []
lambda_h_bases = []

mu_h = []
mu_h_bases = []

p = []
p_bases = []

k = []
k_bases = []

c = []
c_bases = []

health_model = []
health_model_bases = []

discount = ['d100']
discount_bases = [1.00]

insures = ['emp', 'act']
insures_bases = ['Fixed', 'Actuarial']

actuarial_scale = 1
actuarial_admin_cost = 0

def est_emp_insurance_price(shock_size):
    return shock_size/6

#######################################
# un/mute everything between bands 

fitness_r = ['fr1.0']
fitness_r_bases = [1.0]

lambda_h = ['lam10']
lambda_h_bases = [10]

mu_h = ['mu1']
mu_h_bases = [1.0]

health_model = ['steve']
health_model_bases = ['HealthDependentSteve']


# keep muted shows options
#health_model = ['steve', 'dustin']
#health_model_bases = ['HealthDependentSteve', 'HealthDependentDustin']

#####################################
# mute or unmute not whatever was done above

#p = ['p1']
#p_bases = [1]

#k = ['k.5']
#k_bases = [0.5]

#c = ['c2']
#c_bases = [2]

#health_model = ['fan']
#health_model_bases = ['HealthDependentFan']

#########################################

#max_shocks = ['ms6', 'ms8']
#max_shocks_bases = [6, 8]

#size = ['s75', 's90', 's105']
#size_bases = [75, 90, 105]

#alpha = ['a10', 'a125', 'a15']
#alpha_bases = [0.1, 0.125, 0.15]

#beta = ['b02', 'b03', 'b04', 'b05']
#beta_bases = [0.02, 0.03, 0.04, 0.05]

#discount = ['d80', 'd90', 'd100']
#discount_bases = [0.80, 0.90, 1.00]

#eta = ['e60', 'e70']
#eta_bases = ['0.60', '0.70']

#gamma_c = ['gc5', 'gc10']
#gamma_c_bases = [5, 10]

#gamma_h = ['gh10', 'gh20']
#gamma_h_bases = [10, 20]

#fit_degen = ['d15','d20','d25']
#fit_degen_bases = [0.15, 0.20, 0.25]

#fit_price = ['p500', 'p600']
#fit_price_bases = [5.0, 6.0]

#fitness_r = ['fr2.0', 'fr3.0', 'fr4.0']
#fitness_r_bases = [2.0, 3.0, 4.0]

#lambda_h = ['lam0']
#lambda_h_bases = [0.0]

#p = []
#p_bases = []

#k = []
#k = []

#c = []
#c = []

#health_model = ['steve', 'dustin', 'fan']
#health_model_bases = ['HealthDependentSteve', 'HealthDependentDustin', 'HealthDependentFan']

#insures = ['emp', 'act']
#insures_bases = ['Fixed', 'Actuarial']

all_options = [max_shocks, size, alpha, beta, eta, gamma_c, gamma_h, fit_degen, fit_price, fitness_r, lambda_h, mu_h, p, k, c, discount, health_model, insures]
all_bases = [max_shocks_bases, size_bases, alpha_bases, beta_bases, eta_bases, gamma_c_bases, gamma_h_bases, fit_degen_bases, fit_price_bases, fitness_r_bases, lambda_h_bases, mu_h_bases, p_bases, k_bases, c_bases, discount_bases, health_model_bases, insures_bases]
titles = ['NShocks', 'Size', 'Alpha', 'Beta', 'Eta', 'GammaC', 'GammaH', 'FitDegen', 'FitPrice', 'FitR', 'Lambda', 'Mu', 'P','K','C','Discount', 'HealthFunc', 'Ins']
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

out['joy'] = {}
out['probability'] = {}

out['fitnesses'] = [{'type' : 'ProportionalLoss'}, {'type' : 'FixedPrice'}]

def add_options(dicts, title, option_name, parent = '', sub_parent = ''): 
    if not bases_dict[title]:
        return dicts
    new_dicts = []
    for cur_out in dicts:
        for value in bases_dict[title]:
            out2 = copy.deepcopy(cur_out)
            if parent:
                if type(parent) != list:
                    parent = [parent]
                for par in parent:
                    if sub_parent != '':
                        out2[par][sub_parent][option_name] = value
                    else:
                        out2[par][option_name] = value
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
dicts = add_options(dicts, 'NShocks', 'max_shocks')
dicts = add_options(dicts, 'Size', 'shock_income_size')
dicts = add_options(dicts, 'GammaC', 'gamma_consumption', 'joy')
dicts = add_options(dicts, 'GammaH', 'gamma_health', 'joy')
dicts = add_options(dicts, 'Alpha', 'alpha', 'probability')
dicts = add_options(dicts, 'Beta', 'beta', 'probability')
dicts = add_options(dicts, 'Eta', 'eta', 'probability')
dicts = add_options(dicts, 'FitDegen', 'rate', 'fitnesses', 0)
dicts = add_options(dicts, 'FitPrice', 'price', 'fitnesses', 1)
dicts = add_options(dicts, 'Discount', 'discount')
dicts = add_options(dicts, 'FitR', 'fitness_r', ['joy', 'probability'])
dicts = add_options(dicts, 'Lambda', 'lambda', ['joy', 'probability'])
dicts = add_options(dicts, 'Mu', 'mu', ['joy','probability'])
dicts = add_options(dicts, 'P', 'p', ['joy', 'probability'])
dicts = add_options(dicts, 'K', 'k', ['joy', 'probability'])
dicts = add_options(dicts, 'C', 'c', ['joy','probability'])
dicts = add_options(dicts, 'HealthFunc', 'type', ['joy', 'probability'])
dicts = add_ins_options(dicts)

for s in dicts:
    s['max_savings'] = int(s['shock_income_size'])
    s['min_savings'] = -int(2 * s['shock_income_size'])
    penalty = 0
    if s['insurance']['type'] == 'Fixed':
        penalty = est_emp_insurance_price(s['shock_income_size'] * 3/4)
    s['job'] = {
        'type' : 'AgeLinear',
        'intercept' : 55 - penalty,
        'slope' : 1
    }

for out in dicts:
    options = [bases_options_dict[t][v] for t,v in out['treatments'].items()]
    with open('_'.join(options) + '.json', 'w') as outfile:
        json.dump(out, outfile, indent=4)
