import os
import random
import sys
from array import array
from itertools import chain
import json

def parse_line(line):
    return line.strip("\n").split(",")


def get_min_max(stream, index, init_offset, offset_increment):
    stream.seek(init_offset)
    min_val = int(parse_line(stream.readline())[index])
    prev_val = min_val
    cur_val = prev_val
    count = 0
    while cur_val >= prev_val:
        count += 1
        stream.seek(init_offset + count * offset_increment)
        prev_val = cur_val
        line = stream.readline()
        cur_val = int(parse_line(line)[index])
    max_val = prev_val
    return (min_val, max_val)


def get_data_features(filename):
    f = open(filename)

    header_len = 0
    header = f.readline()
    header_len += len(header)
    header = header.strip("\n").split(",")
    header_indices = {header[i]: i for i in range(len(header))}

    line = f.readline()
    line_len = len(line)
    # Add this in mingw.
    # header_len += 1
    # line_len += 1

    (min_cash, max_cash) = get_min_max(f, header_indices["Cash"], header_len, line_len)
    n_cash = max_cash - min_cash + 1
    (min_fitness, max_fitness) = get_min_max(
        f, header_indices["Fitness"], header_len, line_len * n_cash
    )
    n_fitness = max_fitness - min_fitness + 1
    (min_shocks, max_shocks) = get_min_max(
        f, header_indices["Shocks"], header_len, line_len * n_cash * n_fitness
    )
    n_shocks = max_shocks - min_shocks + 1
    (min_age, max_age) = get_min_max(
        f, header_indices["Age"], header_len, line_len * n_cash * n_fitness * n_shocks
    )
    f.close()
    return (
        (header_len, line_len),
        {
            "max_age": max_age,
            "max_shocks": max_shocks,
            "max_fitness": max_fitness,
            "max_cash": max_cash,
            "min_cash": min_cash,
        },
        header,
    )


def process_line(raw_line):
    line = raw_line.strip("\n").split(",")
    return dict(zip(header, line))


def get_index(state):
    return (
        (max_age - state[0]) * meta_grid_size
        + state[1] * grid_size
        + state[2] * row_size
        + (state[3] - min_cash)
    ) * 2


def select_state(fstream, state):
    fstream.seek(offsets[0] + offsets[1] * get_index(state))
    no_shock = process_line(fstream.readline())
    shock = process_line(fstream.readline())
    return [no_shock, shock]


filename_base = sys.argv[1]
random.seed(12345679)
filename = filename_base + ".csv"
(offsets, config, header) = get_data_features(filename)

max_age = config["max_age"]
max_shocks = config["max_shocks"]
max_fitness = config["max_fitness"]
max_cash = config["max_cash"]
min_cash = config["min_cash"]
json_config = json.load(open(sys.argv[2], "r"))
decision_periods = json_config.get('decision_periods', max_age)
if decision_periods >= max_age:
    exit()
row_size = max_cash - min_cash + 1
grid_size = (max_fitness + 1) * row_size
meta_grid_size = (max_shocks + 1) * grid_size
header_indices = {header[i]: i for i in range(len(header))}
fstream = open(filename)
f = open(filename_base + "_payout_table.csv", "w+")
f.write(
    ",".join(['Shocks', 'Fitness']) + ',' + ','.join([str(i) for i in range(min_cash, max_cash + 1)]) + '\n'
)
payout_age = decision_periods + 1
for shocks in range(0, max_shocks + 1):
  for fitness in range(0, max_fitness + 1):
    f.write(','.join([str(shocks), str(fitness)]))
    for cash in range(min_cash, max_cash + 1):
      state = select_state(fstream, [payout_age, shocks, fitness, cash])
      exp_value = float(state[0]['Utility']) * float(state[0]['Probability']) + float(state[1]['Utility']) * float(state[1]['Probability'])
      f.write(',' + str(int(exp_value)))
    f.write('\n')

