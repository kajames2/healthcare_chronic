#!/usr/bin/env python3

import json
import os
import copy
import time
from shutil import copyfile
import sys


def generate_non_combos(config, variations):
    out_templates = []
    name_sets = []
    for var in variations:
        new_templates, new_names = vary_template(config, var)
        out_templates += new_templates
        name_sets.append(new_names)
    return out_templates, name_sets


def generate_all_combos(config, variations):
    out_templates = [config]
    name_sets = []
    for var in variations:
        new_out_templates = []
        for template in out_templates:
            new_templates, new_names = vary_template(template, var)
            new_out_templates += new_templates
        name_sets.append(new_names)
        out_templates = new_out_templates
    return out_templates, name_sets


def vary_template(config, var):
    var.pop("_COMMENT", None)
    for key in var.keys():
        if type(var[key]) is not list:
            var[key] = [var[key]]
    covary_lengths = [len(val) for val in var.values()]
    if len(set(covary_lengths)) > 1:
        print("covarying lengths are not equal: ", var)
        exit()
    n_vars = covary_lengths[0]
    out_templates = []
    names = [''] * n_vars
    for i in range(n_vars):
        conf = copy.deepcopy(config["config"])
        name = config["name"]
        for key in var.keys():
            conf_mod = conf
            val = var[key][i]
            subkeys = key.split(':')
            sub_name = gen_name(subkeys, val, i)
            names[i] += '_' + sub_name
            name += '_' + sub_name
            subkeys = [int(val) if val.isdigit() else val for val in subkeys]
            for j in range(len(subkeys) - 1):
                conf_mod = conf_mod[subkeys[j]]
            if type(val) is dict:
                conf_mod = conf_mod[subkeys[-1]]
                for key in val:
                    conf_mod[key] = val[key]
            else:
                conf_mod[subkeys[-1]] = val
        out_templates.append({"name": name, "config": conf})
    names = [name.strip('_') for name in names]
    return out_templates, names


def gen_name(sub_keys, val, i):
    shortened_keys = {
        'max_age': 'maxage',
        'max_fitness': 'maxfit',
        'min_debt_payment': 'minpay',
        'shock_count_size': 'ssizec',
        'job': 'job',
        'joy': 'joy',
        'probability': 'prob',
        'fitnesses': 'fit',
        'max_shocks': 'maxs',
        'shock_income_size': 'ssizei',
        'discount': 'beta',
        'insurance': 'ins',
        'max_savings': 'maxs',
        'min_savings': 'mins',
        'type': 't',
        'intercept': 'b',
        'slope': 'm',
        'j': 'j',
        'mods': 'mods',
        'func': 'f',
        'param': '',
        'max_modification': 'mm',
        'age_coeff': 'ac',
        'shock_coeff': 'sc',
        'age_rate': 'ar',
        'shock_rate': 'sr',
        'rate': 'r',
        'price': 'p',
        'scale': 's',
        'admin_cost': 'acost',
        'FlatLoss': 'FL',
        'ProportionalLoss': 'PL',
        'Multiply': 'Mul',
        'Add': 'Add',
        'Linear': 'Lin',
        'Fractional': 'Fr ac',
        'Constant': 'Con',
        'Cosine': 'Cos',
        'Age': 'A',
        'Shocks': 'S',
        'Fitness': 'F'
    }
    name = shortened_keys.get(sub_keys[0], sub_keys[0])
    if (len(sub_keys) > 1):
        name += shortened_keys.get(sub_keys[-1], sub_keys[-1])
    if type(val) is dict:
        for key in val:
            valstr = str(val[key]).replace('.', '')
            name += shortened_keys.get(valstr, valstr)
    elif type(val) is list:
        name += str(i)
    else:
        valstr = str(val).replace('.', '')
        name += shortened_keys.get(valstr, valstr)
    return name


def write_configs(configs, base_name):
    timestr = time.strftime("%m%d%y_%H%M%S")
    unique_dir_name = base_name + "_" + timestr
    os.mkdir(unique_dir_name)
    for config in configs:
        with open(
                unique_dir_name + '/' + config['name'].strip('_') +
                '_conf.json', 'w') as outfile:
            json.dump(config['config'], outfile, indent=4)
    return unique_dir_name


def main():
    if len(sys.argv) != 2:
        print("Error: expects exactly one argument")
        print("\\write_configs2.py config_name")
        exit

    filename = sys.argv[1]
    with open(filename, "r") as f:
        temp_dic = json.load(f)
    template = temp_dic["template"]
    base_name = temp_dic.get("name", template)
    all_combos = temp_dic.get("all_combos", True)
    variations = temp_dic["variations"]
    template_json = json.load(open(template + ".json", "r"))
    out_configs = None
    name_sets = None
    if not all_combos:
        out_configs, name_sets = generate_non_combos(
            {
                "name": '',
                "config": template_json
            }, variations)
    else:
        out_configs, name_sets = generate_all_combos(
            {
                "name": '',
                "config": template_json
            }, variations)
    dir_name = write_configs(out_configs, base_name)
    copyfile(filename, dir_name + "/" + filename)
    copyfile(template + ".json", dir_name + "/" + template + ".json")
    with open(dir_name + '/subnames_lists.json', 'w') as outfile:
        json.dump(name_sets, outfile, indent=4)


if __name__ == "__main__":
    main()
