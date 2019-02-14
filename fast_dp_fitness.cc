#include <omp.h>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include "dp/decision_cache.h"
#include "dp/storage.h"
#include "healthcare/configuration.h"
#include "healthcare/configuration/reader.h"
#include "healthcare/decision.h"
#include "healthcare/decision_results.h"
#include "healthcare/person.h"
#include "healthcare/person_income.h"

using namespace healthcare;
using namespace dp;

std::pair<boost::filesystem::path, boost::filesystem::path> GetPaths(
    int argc, char** argv);
void RunOptimization(const Configuration& config, std::string out_dir,
                     std::string basename);
std::vector<PersonIncome> CreateTemplateStates(int age,
                                               const Configuration& config);

void StoreAgeOptimals(Storage& storage, Storage& min_storage,
                      std::function<float(const Person&)> opt_lookup,
                      const DecisionCache& dec_cache,
                      const std::vector<PersonIncome>& init_states,
                      const Configuration& config);

template <class T>
std::vector<T> JoinVectors(std::vector<T> v1, std::vector<T> v2);

//  Risk aversion ex:  Take sqrt of LE function.
auto util = [](float joy) -> float { return joy; };

float ExpectedUtility(const DecisionResults& res) {
  return res.result.value * res.result.probability +
         res.result_shock.value * res.result_shock.probability;
}

int main(int argc, char** argv) {
  using namespace boost::filesystem;
  try {
    std::pair<path, path> paths = GetPaths(argc, argv);
    path input = paths.first;
    path out_dir = paths.second;
    const Configuration config =
        configuration::ReadConfigurationFile(input.string());
    RunOptimization(config, out_dir.string(), input.stem().string());
  } catch (const char* msg) {
    std::cerr << msg << std::endl;
    return 1;
  } catch (const boost::program_options::error& ex) {
    std::cerr << ex.what() << std::endl;
    return 1;
  }
}

std::pair<boost::filesystem::path, boost::filesystem::path> GetPaths(
    int argc, char** argv) {
  using namespace boost::program_options;
  using namespace boost::filesystem;
  options_description desc("Options");
  desc.add_options()("help,h", "Help screen")(
      "i", value<std::string>(), "Input Filename")("o", value<std::string>(),
                                                   "Output Directory");
  variables_map vm;
  store(parse_command_line(argc, argv, desc), vm);
  notify(vm);

  if (vm.count("help")) {
    std::cout << desc << "\n";
    throw "";
  }

  if (!vm.count("i")) {
    throw "No input configuration file provided.";
  }

  if (!vm.count("o")) {
    std::cout << "No output directory provided. Assuming current directory."
              << std::endl;
  }

  path input(vm["i"].as<std::string>());
  path out_dir = vm.count("o") ? path(vm["o"].as<std::string>()) : path(".");

  if (!exists(input) || !is_regular_file(input)) {
    throw "Input file does not exist or is not a regular file.";
  }

  if (!exists(out_dir) || !is_directory(out_dir)) {
    throw "Output directory does not exist or is not a valid directory.";
  }

  return std::pair<path, path>(input, out_dir);
}

void RunOptimization(const Configuration& config, std::string out_dir,
                     std::string basename) {
  std::string max_filename = out_dir + '/' + basename + ".csv";
  std::ofstream max_stream(max_filename, std::ofstream::out);
  // std::string min_filename = out_dir + '/' + basename + "_min.csv";
  // std::ofstream min_stream(min_filename, std::ofstream::out);
  max_stream << "Age,Shocks,Fitness,Cash,"
                "FitnessSpending,JoySpending,InsuranceSpending,"
                "NextAge,NextShocks,NextFitness,NextCash,"
                "Probability,Enjoyment,FutureValue,Value\n";

  Storage opt(config);
  Storage min(config);

  for (int age = config.max_age; age >= 1; --age) {
    std::cerr << age << "..." << std::flush;
    std::cerr << "making_cache..." << std::flush;
    DecisionEvaluator evaluator(config, age);
    DecisionCache dec_cache(config, evaluator, age);

    std::cerr << "calculating_optimals..." << std::flush;
    std::vector<PersonIncome> init_states = CreateTemplateStates(age, config);
    if (age == config.max_age) {
      StoreAgeOptimals(opt, min, [](const Person&) { return 0; }, dec_cache,
                       init_states, config);
    } else {
      Storage opt_cpy = opt;
      StoreAgeOptimals(
          opt, min, [&opt_cpy](const Person& p) { return opt_cpy.GetValue(p); },
          dec_cache, init_states, config);
    }
    std::cerr << "writing_to_file..." << std::flush;
    max_stream << opt << std::endl;
    std::cerr << "done!" << std::endl;
    // min_stream << min << std::endl;
  }

  max_stream.close();
  // min_stream.close();
}

std::vector<PersonIncome> CreateTemplateStates(int age,
                                               const Configuration& config) {
  std::vector<PersonIncome> init_states;
  init_states.reserve((config.max_shocks + 1) * (config.max_fitness + 1) *
                      (config.max_savings - config.min_savings + 1));
  for (int s = 0; s <= config.max_shocks; ++s) {
    for (int f = 0; f <= config.max_fitness; ++f) {
      int i = config.job->GetEarnings(age);
      for (int c = config.min_savings; c <= config.max_savings; ++c) {
        int b =
            c >= 0
                ? i + c
                : std::max(0, static_cast<int>(
                                  i + std::ceil(c * config.min_debt_payment)));
        init_states.push_back({{age, s, f, c}, b, i});
      }
    }
  }
  return init_states;
}

void StoreAgeOptimals(Storage& storage, Storage& storage_min,
                      std::function<float(const Person&)> opt_lookup,
                      const DecisionCache& dec_cache,
                      const std::vector<PersonIncome>& init_states,
                      const Configuration& config) {
  std::vector<DecisionResults> dec_states;
  // Performance critical loop.  Be careful when modifying.
#pragma omp parallel for private(dec_states)
  for (int cur = 0; cur < init_states.size(); ++cur) {
    PersonIncome cur_state = init_states[cur];
    auto start_it =
        dec_cache.begin(cur_state.shocks, cur_state.fitness, cur_state.budget);
    auto end_it =
        dec_cache.end(cur_state.shocks, cur_state.fitness, cur_state.budget);
    size_t n_decisions = std::distance(start_it, end_it);
    dec_states.resize(n_decisions);
    std::copy(start_it, end_it, dec_states.begin());
    std::for_each(
        dec_states.begin(), dec_states.end(),
        [&opt_lookup, &cur_state, &config](DecisionResults& pair) -> void {
          pair.result.person.cash =
              cur_state.cash + cur_state.income - pair.result.spending;
          pair.result.person.cash = std::clamp(
              pair.result.person.cash, config.min_savings, config.max_savings);
          pair.result.future_value = opt_lookup(pair.result.person);
          pair.result.value +=
              pair.result.joy + config.discount * pair.result.future_value;

          pair.result_shock.person.cash =
              cur_state.cash + cur_state.income - pair.result_shock.spending;
          pair.result_shock.person.cash =
              std::clamp(pair.result_shock.person.cash, config.min_savings,
                         config.max_savings);
          pair.result_shock.future_value = opt_lookup(pair.result_shock.person);
          pair.result_shock.value +=
              pair.result_shock.joy +
              config.discount * pair.result_shock.future_value;
          pair.value = ExpectedUtility(pair);
        });

    auto opts = std::minmax_element(
        dec_states.begin(), dec_states.end(),
        [](const DecisionResults& p1, const DecisionResults& p2) -> bool {
          return p1.value < p2.value;
        });

    storage.StoreResult(init_states[cur], *opts.second);
    storage_min.StoreResult(init_states[cur], *opts.first);
  }
}
