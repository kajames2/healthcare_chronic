#!/usr/bin/env python3

import itertools
import json
import sys

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import pandas as pd
from matplotlib.backends.backend_pdf import PdfPages

# These can be changed easily
display_cols = [
    "Cash",
    "Shocks",
    "ShockProb",
    "Shocked",
    "AtMaxShocks",
    "DieFrac",
    "NextFitness",
    "BuyIns",
    "Enjoyment",
    "TotalJoy",
    "JoySpending",
    "FitnessSpending",
    "InsuranceSpending",
    "NextCash",
    "TotalInsurancePayout",
    "TotalInsuranceSpending",
    "NetInsurerProfit"
]


def main():
    if len(sys.argv) != 2:
        print("Error: expects exactly one argument")
        print("\\plot_maker.py dir_name")
        exit

    dir_name = sys.argv[1]
    flex = json.load(open(dir_name + "/subnames_lists.json", "r"))
    n = len(flex)
    out_file_sets = []
    out_filenames = []
    filenames = []
    for i in range(n):
        i_params = list(itertools.product(*(flex[:i] + flex[i + 1 :])))
        for param_set in i_params:
            out_param_set = []
            filename = list(param_set)
            filename.insert(i, "X")
            out_filenames.append("_".join(filename))
            for val in flex[i]:
                i_params_new = list(param_set)
                i_params_new.insert(i, val)
                out_param_set.append((val, "_".join(i_params_new)))
                filenames.append("_".join(i_params_new))
            out_file_sets.append(out_param_set)

    all_treatments = list(set(filenames))
    for condition_on_alive in [True, False]:
        print("Reading Data..." + str(condition_on_alive))
        treatment_means = {
            treat: get_file_means(dir_name, treat, condition_on_alive)
            for treat in all_treatments
        }
        print("Done!  Now processing...")

        colors = [
            "blue",
            "red",
            "green",
            "orange",
            "magenta",
            "cyan",
            "black",
            "yellow",
        ]
        ages = treatment_means[all_treatments[0]]["Age"].tolist()
        for (data, outname) in zip(out_file_sets, out_filenames):
            ext = ""
            if condition_on_alive:
                ext = "_dd"
            with PdfPages(dir_name + "/" + outname + ext + ".pdf") as pdf:
                for col in display_cols:
                    plt.figure(figsize=(6, 6))
                    for i in range(len(data)):
                        plt.plot(
                            list(
                                range(
                                    1,
                                    len(treatment_means[data[i][1]][col].tolist()) + 1,
                                )
                            ),
                            treatment_means[data[i][1]][col].tolist(),
                            linewidth=2,
                            color=colors[i],
                            label=data[i][0],
                        )
                    plt.title(col)
                    plt.legend()
                    pdf.savefig()
                    plt.close()


def get_file_means(dir_name, filebase, condition_on_alive):
    df = pd.read_csv(dir_name + "/" + filebase + "_conf_rand_lives.csv")
    if condition_on_alive:
        df = df.loc[df["AtMaxShocks"] == 0]
    df = df.groupby(["Age"], as_index=False).mean()
    df.loc[df["Dies"] == 0, "DieFrac"] = 0
    df.loc[df["Dies"] > 0, "DieFrac"] = df["Dies"] / (
        1 - df["AtMaxShocks"] + df["Dies"]
    )
    return df


if __name__ == "__main__":
    main()
