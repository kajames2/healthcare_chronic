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


def next_state(row):
    return [
        int(row["NextAge"]),
        int(row["NextShocks"]),
        int(row["NextFitness"]),
        int(row["NextCash"]),
    ]


def get_life_random(fstream, start_state, max_age):
    rands = [random.uniform(0, 1) for i in range(0, max_age)]
    return get_life_with_draws(fstream, start_state, rands)


def get_life_with_draws(fstream, start_state, draws):
    life = []
    state = start_state
    while state[0] <= max_age:
        rand = draws[state[0] - 1]
        row_pair = select_state(fstream, state)
        probs = [float(row["Probability"]) for row in row_pair]
        if rand <= probs[1]:
            row = row_pair[1]
            shocked = 1
        else:
            row = row_pair[0]
            shocked = 0
        out_row = list(row.values())
        out_row.append("{0:8.6f}".format(rand))
        out_row.append("{0:1}".format(shocked))
        life.append(out_row)
        state = next_state(row)
    return life


def generate_fair_draws(max_age, n_lives):
    n_segments = 3
    base_segments = []
    for i in range(n_segments):
        base_segments.append(list(range(i + 1, max_age + 1, n_segments)))
    fair_draws = []
    for i in range(0, n_lives // 2):
        rand_segments = [
            random.sample(segment, len(segment)) for segment in base_segments
        ]
        sample = []
        segment_samples = random.sample(rand_segments, n_segments)
        for seg in segment_samples:
            sample += seg
        antithetic = [max_age + 1 - s for s in sample]
        fair_draws.append([stratified_sample(s, max_age) for s in sample])
        fair_draws.append([stratified_sample(s, max_age) for s in antithetic])
    if n_lives % 2 == 1:
        rand_segments = [
            random.sample(segment, len(segment)) for segment in base_segments
        ]
        sample = chain(*rand_segments)
        fair_draws.append([stratified_sample(s, max_age) for s in sample])
    return fair_draws


def stratified_sample(segment, n_segments):
    segment_size = 1 / n_segments
    return random.uniform((segment - 1) / n_segments, segment / n_segments)


filenames = sys.argv[1:]
for filename_base in filenames:
    random.seed(12345679)
    filename = filename_base + ".csv"
    (offsets, config, header) = get_data_features(filename)

    max_age = config["max_age"]
    max_shocks = config["max_shocks"]
    max_fitness = config["max_fitness"]
    max_cash = config["max_cash"]
    min_cash = config["min_cash"]
    row_size = max_cash - min_cash + 1
    grid_size = (max_fitness + 1) * row_size
    meta_grid_size = (max_shocks + 1) * grid_size
    print(config)
    header_indices = {header[i]: i for i in range(len(header))}
    n_lives = 10000
    lives_digits = len(str(abs(n_lives - 1)))
    start_state = [1, 0, 20, 0]
    fstream = open(filename)
    rand_lives = [get_life_random(fstream, start_state, max_age) for i in range(n_lives)]
    #rands = generate_fair_draws(max_age, n_lives)
    #rand_lives = [get_life_with_draws(fstream, start_state, draws) for draws in rands]
    f = open(filename_base + "_rand_lives.csv", "w+")
    f.write(
        ",".join(header)
        + ",RandDraw,Shocked,TotalJoy,BuyIns,TotalInsuranceSpending,InsurancePayout,TotalInsurancePayout,NetInsurerProfit,ShockProb,AtMaxShocks,Dies,Life\n"
    )
    json_config = json.load(open(filename_base + ".json", "r"))
    shock_size = json_config["shock_income_size"]
    for life in range(n_lives):
        tot_enjoyment = 0.0
        total_insurance_spending = 0
        total_payout = 0
        prev_at_max_shocks = 0
        total_insurer_profit = 0
        for period in rand_lives[life]:
            shocked = int(period[-1])
            tot_enjoyment += float(period[header_indices["Enjoyment"]])
            total_insurance_spending += int(period[header_indices["InsuranceSpending"]])
            buy_ins = int(int(period[header_indices["InsuranceSpending"]]) > 0)
            shock_prob = shocked * (float(period[header_indices["Probability"]])) + (
                1 - shocked
            ) * (1 - float(period[header_indices["Probability"]]))
            payout = buy_ins * shocked * shock_size
            total_payout += payout
            total_insurer_profit += int(period[header_indices["InsuranceSpending"]]) - payout
            at_max_shocks = int(int(period[header_indices["Shocks"]]) == max_shocks)
            died = at_max_shocks - prev_at_max_shocks
            prev_at_max_shocks = at_max_shocks
            period.append("{0:8.4f}".format(tot_enjoyment))
            period.append("{0:1}".format(buy_ins))
            period.append("{0:4}".format(total_insurance_spending))
            period.append("{0:4f}".format(payout))
            period.append("{0:4f}".format(total_payout))
            period.append("{0:4f}".format(total_insurer_profit))
            period.append("{0:8.6f}".format(shock_prob))
            period.append("{0:1}".format(at_max_shocks))
            period.append("{0:1}".format(died))
            period.append("{0:3}".format(life))
            f.write(",".join(period) + "\n")
