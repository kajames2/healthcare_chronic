#include "healthcare/configuration.h"
#include <memory>
#include <string>
#include <unordered_map>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "configuration/fitness_reader.h"
#include "configuration/insurance_reader.h"
#include "configuration/job_reader.h"
#include "configuration/joy_reader.h"
#include "configuration/prob_reader.h"
#include "configuration/utility_reader.h"
#include "exprtk.hpp"

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
  config.job = configuration::ReadJob(root.get_child("job"), config.max_age,
                                      config.max_shocks, config.max_fitness);
  config.fitness =
      configuration::ReadFitness(root.get_child("fitness"), config.max_age,
                                 config.max_shocks, config.max_fitness);
  config.joy = configuration::ReadJoy(root.get_child("joy"), config.max_age,
                                      config.max_shocks, config.max_fitness);
  config.shock_prob =
      configuration::ReadProb(root.get_child("probability"), config.max_age,
                              config.max_shocks, config.max_fitness);
  config.shock_income_size = root.get<int>("shock_income_size");
  config.shock_count_size = root.get<int>("shock_count_size");
  config.insurance =
      configuration::ReadInsurance(root.get_child("insurance"), config);

  config.max_budget = CalculateMaxBudget(config);
  if (root.count("utility") == 0) {
    config.utility = [](int, int, int, float joy) { return joy; };
  } else {
    config.utility =
        configuration::ReadUtility(root.get_child("utility"), config.max_age,
                                   config.max_shocks, config.max_fitness);
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
  for (int age = 0; age <= config.max_age; ++age) {
    for (int shocks = 0; shocks <= config.max_shocks; ++shocks) {
      for (int fitness = 0; fitness <= config.max_fitness; ++fitness) {
        if (config.job(age, shocks, fitness) > max_income) {
          max_income = config.job(age, shocks, fitness);
        }
      }
    }
  }
  return max_income + config.max_savings;
}

}  // namespace healthcare
