#include <omp.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <utility>

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <vector>
#include "dp/decision_cache.h"
#include "dp/storage.h"
#include "healthcare/configuration.h"
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

void StoreAgeOptimals(Storage& storage, Storage& pess_storage,
                      std::function<float(const Person&)> opt_lookup,
                      const DecisionCache& dec_cache,
                      const std::vector<PersonIncome>& init_states,
                      const Configuration& config);

template <class T>
std::vector<T> JoinVectors(std::vector<T> v1, std::vector<T> v2);

float ExpectedUtility(const DecisionResults& res) {
  return res.result.utility * res.result.subj_prob +
         res.result_shock.utility * res.result_shock.subj_prob;
}

int main(int argc, char** argv) {
  using namespace boost::filesystem;
  try {
    std::pair<path, path> paths = GetPaths(argc, argv);
    path input = paths.first;
    path out_dir = paths.second;
    const Configuration config = ReadConfigurationFile(input.string());
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
  max_stream << "Age,Shocks,Fitness,Cash,"
                "FitnessSpending,JoySpending,InsuranceSpending,BuyIns,"
                "NextAge,NextShocks,NextFitness,NextCash,"
                "Probability,ProbabilitySubj,ShockProbability,"
                "ShockProbabilitySubj,NoShockProbabilitySubj,SuddenDeathProb,"
                "NoSuddenDeathProbSubj,Enjoyment,"
                "ImmediateUtility,FutureUtility,Utility\n";
  Storage opt(config);

  std::ofstream min_stream;
  if (config.save_pessimal) {
    std::string min_filename = out_dir + '/' + basename + "_min.csv";
    min_stream = std::ofstream(min_filename, std::ofstream::out);
    min_stream << "Age,Shocks,Fitness,Cash,"
                  "FitnessSpending,JoySpending,InsuranceSpending,BuyIns,"
                  "NextAge,NextShocks,NextFitness,NextCash,"
                  "Probability,ProbabilitySubj,ShockProbability,"
                  "ShockProbabilitySubj,NoShockProbabilitySubj,SuddenDeathProb,"
                  "NoSuddenDeathProbSubj,Enjoyment,"
                  "ImmediateUtility,FutureUtility,Utility\n";
  }

  Storage pess(config);

  for (int age = config.max_age; age >= 1; --age) {
    std::cerr << std::string(80, ' ') << std::flush << '\r';
    std::cerr << age << "..." << std::flush;
    std::cerr << "making_cache..." << std::flush;
    std::cout << config.shock_prob(1, 0, 75) << std::endl;
    auto evaluator = std::make_unique<DecisionEvaluator>(config, age);
    std::cout << "here" << std::endl;
    std::cout << config.shock_prob(1, 0, 75) << std::endl;
    auto dec_cache = std::make_unique<DecisionCache>(config, *evaluator, age);
    std::cout << config.shock_prob(1, 0, 75) << std::endl;
    std::cerr << "calculating_optimals..." << std::flush;
    std::vector<PersonIncome> init_states = CreateTemplateStates(age, config);
    if (age == config.max_age) {
      StoreAgeOptimals(
          opt, pess, [](const Person&) { return 0; }, *dec_cache, init_states,
          config);
    } else {
      Storage opt_cpy = opt;
      StoreAgeOptimals(
          opt, pess,
          [&opt_cpy](const Person& p) { return opt_cpy.GetValue(p); },
          *dec_cache, init_states, config);
    }
    std::cerr << "writing_to_file..." << std::flush;
    if (config.save_pessimal) {
      min_stream << pess << std::endl;
    }
    max_stream << opt << std::endl;
    std::cerr << "done!" << std::flush << '\r';
  }

  max_stream.close();
  if (config.save_pessimal) {
    min_stream.close();
  }
}

std::vector<PersonIncome> CreateTemplateStates(int age,
                                               const Configuration& config) {
  std::vector<PersonIncome> init_states;
  init_states.reserve((config.max_shocks + 1) * (config.max_fitness + 1) *
                      (config.max_savings - config.min_savings + 1));
  for (int shocks = 0; shocks <= config.max_shocks; ++shocks) {
    for (int fitness = 0; fitness <= config.max_fitness; ++fitness) {
      int income = config.job(age, shocks, fitness);
      for (int savings = config.min_savings; savings <= config.max_savings;
           ++savings) {
        int budget =
            savings >= 0
                ? income + savings
                : std::max(0, static_cast<int>(
                                  income + std::ceil(savings *
                                                     config.min_debt_payment)));
        init_states.push_back(
            {{age, shocks, fitness, savings}, budget, income});
      }
    }
  }
  return init_states;
}

void StoreAgeOptimals(Storage& storage, Storage& pess_storage,
                      std::function<float(const Person&)> opt_lookup,
                      const DecisionCache& dec_cache,
                      const std::vector<PersonIncome>& init_states,
                      const Configuration& config) {
  std::vector<DecisionResults> dec_states;
// Performance critical loop.  Be careful when modifying.
#pragma omp parallel for private(dec_states)
  for (int cur = 0; cur < init_states.size(); ++cur) {
    PersonIncome cur_state = init_states[cur];
    bool is_dead = cur_state.shocks >= config.max_shocks;
    if (is_dead) {
      auto opt = DecisionResults{Decision(), PeriodResult(), PeriodResult(), 0};
      Person next_person = cur_state;
      next_person.age += 1;
      opt.result.person = next_person;
      opt.result_shock.person = next_person;
      storage.StoreResult(init_states[cur], opt);
      pess_storage.StoreResult(init_states[cur], opt);
    } else {
      auto start_it = dec_cache.begin(cur_state.shocks, cur_state.fitness,
                                      cur_state.budget);
      auto end_it =
          dec_cache.end(cur_state.shocks, cur_state.fitness, cur_state.budget);
      size_t n_decisions = std::distance(start_it, end_it);
      dec_states.resize(n_decisions);
      std::copy(start_it, end_it, dec_states.begin());
      for (auto& pair : dec_states) {
        auto& res = pair.result;
        auto& res_shock = pair.result_shock;
        res.person.cash = cur_state.cash + cur_state.income - res.spending;
        res.person.cash =
            std::clamp(res.person.cash, config.min_savings, config.max_savings);

        res.future_utility = opt_lookup(res.person);
        res.utility += res.immediate_utility + config.discount *
                                                   res.subj_no_death_prob *
                                                   res.future_utility;
        res_shock.person.cash =
            cur_state.cash + cur_state.income - res_shock.spending;
        res_shock.person.cash = std::clamp(
            res_shock.person.cash, config.min_savings, config.max_savings);
        res_shock.future_utility = opt_lookup(res_shock.person);
        res_shock.utility += res_shock.immediate_utility +
                             config.discount * res_shock.subj_no_death_prob *
                                 res_shock.future_utility;

        pair.utility = ExpectedUtility(pair);
      };
      auto opts = std::max_element(
          dec_states.begin(), dec_states.end(),
          [](const DecisionResults& p1, const DecisionResults& p2) -> bool {
            return p1.utility < p2.utility;
          });

      storage.StoreResult(init_states[cur], *opts);

      auto pesses = std::min_element(
          dec_states.begin(), dec_states.end(),
          [](const DecisionResults& p1, const DecisionResults& p2) -> bool {
            return p1.utility < p2.utility;
          });
      pess_storage.StoreResult(init_states[cur], *pesses);
    }
  }
}
