import random
from array import array

# Result features
# Separation across fixed price vs actuarial
# Optimal survives easily

# Additional features
# Add mistaken play

def parse_line(line):
    return line.strip('\n').split(",")

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
        cur_val = int(parse_line(stream.readline())[index])
    max_val = prev_val
    return (min_val, max_val)

def get_data_features(filename):
    f = open(filename);

    header_len = 0
    header = f.readline()
    header_len += len(header)
    header = header.strip('\n').split(",")
    header_indices = {header[i] : i for i in range(len(header))}

    line = f.readline();
    line_len = len(line);
        
    (min_cash, max_cash) = get_min_max(f, header_indices["Cash"], header_len, line_len)
    (min_fitness, max_fitness) = get_min_max(f, header_indices["Fitness"], header_len, line_len * (max_cash - min_cash + 1))
    (min_shocks, max_shocks) = get_min_max(f, header_indices["Shocks"], header_len, line_len * (max_cash - min_cash + 1) * (max_fitness - min_fitness + 1))
    (min_age, max_age) = get_min_max(f, header_indices["Age"], header_len, line_len * (max_cash - min_cash + 1) * (max_fitness - min_fitness + 1) * (max_shocks - min_shocks + 1))
    f.close()
    return ((header_len, line_len), {"max_age" : max_age, "max_shocks" : max_shocks, "max_fitness" : max_fitness, "max_cash" : max_cash, "min_cash" : min_cash}, header)

def process_line(raw_line):
    line = raw_line.strip('\n').split(",")
    return dict(zip(header,line))

def get_index(state) :
    return ((max_age - state[0]) * meta_grid_size + state[1] * grid_size + state[2] * row_size + (state[3] - min_cash)) * 2

def select_state(fstream, state):
    fstream.seek(offsets[0] + offsets[1] * get_index(state))
    no_shock = process_line(fstream.readline())
    shock = process_line(fstream.readline())
    return [no_shock, shock]

def next_state(row):
    return [int(row["NextAge"]), int(row["NextShocks"]), int(row["NextFitness"]), int(row["NextCash"])]

def get_life_random(fstream, start_state):
    life = []
    state = start_state
    while state[0] <= max_age:
        row_pair = select_state(fstream, state)
        probs = [float(row["Probability"]) for row in row_pair]
        rand = random.uniform(0, 1)
        if (rand <= probs[1]):
            row = row_pair[1]
            shocked = 1
        else:
            row = row_pair[0]
            shocked = 0
        out_row = list(row.values())
        out_row.append("{0:5.3f}".format(rand))
        out_row.append("{0:1}".format(shocked))
        life.append(out_row)
        state = next_state(row)
    return life

filenames = ["actuarial_flat_45_100",
             "actuarial_flat_45_95",
             "actuarial_flat_45_90",
             "actuarial_flat_60_100",
             "actuarial_flat_60_95",
             "actuarial_flat_60_90",
             "actuarial_flat_75_100",
             "actuarial_flat_75_95",
             "actuarial_flat_75_90",
             "actuarial_increasing_30_90_100",
             "actuarial_increasing_30_90_95",
             "actuarial_increasing_30_90_90"]
for filename_base in filenames:
    random.seed(12345678)
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
    header_indices = {header[i] : i for i in range(len(header))}
    n_lives = 1000
    lives_digits = len(str(abs(n_lives-1)))
    start_state = [1,0,10,0]
    fstream = open(filename)
    rand_lives = [get_life_random(fstream, start_state) for i in range(n_lives)]
    
    f= open(filename_base + "_rand_lives.csv","w+")
    f.write(','.join(header) + ",RandDraw,Shocked,TotalJoy,BuyIns,InsurancePayout,ShockProb,Life\n")
    for life in range(n_lives):
        tot_enjoyment = 0;
        for period in rand_lives[life]:
            shocked = int(period[-1])
            tot_enjoyment += float(period[header_indices["Enjoyment"]])
            buy_ins = int(int(period[header_indices["InsuranceSpending"]])>0)
            shock_prob = shocked * (float(period[header_indices["Probability"]])) + (1-shocked) * (1 - float(period[header_indices["Probability"]]))
            payout = buy_ins * shocked * 200
            period.append("{0:6.2f}".format(tot_enjoyment))
            period.append("{0:1}".format(buy_ins))
            period.append("{0:3}".format(payout))
            period.append("{0:5.3f}".format(shock_prob))
            period.append("{0:3}".format(life))
            f.write(','.join(period) + '\n')
