#include "healthcare/configuration.h"

#include <memory>
#include <string>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "configuration/fitness_reader.h"
#include "configuration/insurance_reader.h"
#include "configuration/job_reader.h"
#include "configuration/joy_reader.h"
#include "configuration/modulator_reader.h"
#include "configuration/prob_reader.h"
#include "healthcare/modulator/constant.h"

using ::boost::property_tree::ptree;

namespace healthcare {

int CalculateMaxBudget(const Configuration& config);

Configuration ReadConfigurationFile(std::string filename) {
  ptree root;
  read_json(filename, root);
  Configuration config;
  assert(root.count("max_age"));
  assert(root.count("max_fitness"));
  assert(root.count("max_shocks"));
  assert(root.count("max_savings"));
  assert(root.count("min_savings"));
  assert(root.count("job"));

  config.max_age = root.get<int>("max_age");
  config.max_fitness = root.get<int>("max_fitness");
  config.max_shocks = root.get<int>("max_shocks");
  config.max_savings = root.get<int>("max_savings");
  config.min_savings = root.get<int>("min_savings");
  config.min_debt_payment = root.get<float>("min_debt_payment");
  config.job = configuration::ReadJob(root.get_child("job"));
  config.max_budget = CalculateMaxBudget(config);
  config.fitness = configuration::ReadFitnesses(
      root.get_child("fitnesses"), config.max_fitness, config.max_budget);
  config.joy = configuration::ReadJoy(root.get_child("joy"));
  config.shock_prob = configuration::ReadProb(root.get_child("probability"));
  config.shock_income_size = root.get<int>("shock_income_size");
  config.shock_count_size = root.get<int>("shock_count_size");
  config.insurance =
      configuration::ReadInsurance(root.get_child("insurance"), config);

  if (root.count("probability_modulation")) {
    config.shock_prob_mod =
        configuration::ReadModulator(root.get_child("probability_modulation"),
                                     config.max_shocks, config.max_fitness);
  } else {
    config.shock_prob_mod = std::make_unique<modulator::Constant>(
        modulator::Constant::NoModulation());
  }

  if (root.count("joy_modulation")) {
    config.joy_mod =
        configuration::ReadModulator(root.get_child("joy_modulation"),
                                     config.max_shocks, config.max_fitness);
  } else {
    config.joy_mod = std::make_unique<modulator::Constant>(
        modulator::Constant::NoModulation());
  }

  if (root.count("discount") == 0) {
    config.discount = 1;
  } else {
    config.discount = root.get<float>("discount");
  }

  return config;
}

int CalculateMaxBudget(const Configuration& config) {
  int max_income = -1;
  for (int age = config.max_age; age >= 1; --age) {
    if (config.job->GetEarnings(age) > max_income) {
      max_income = config.job->GetEarnings(age);
    }
  }
  return max_income + config.max_savings;
}

}  // namespace healthcare
