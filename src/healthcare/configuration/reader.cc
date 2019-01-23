#include "healthcare/configuration/reader.h"

#include <cassert>
#include <memory>
#include <string>

#include "healthcare/configuration.h"
#include "healthcare/configuration/fitness_reader.h"
#include "healthcare/configuration/insurance_reader.h"
#include "healthcare/configuration/job_reader.h"
#include "healthcare/configuration/joy_reader.h"
#include "healthcare/configuration/prob_reader.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

using namespace boost::property_tree;

namespace healthcare {
namespace configuration {

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
  config.job = ReadJob(root.get_child("job"));
  config.max_budget = CalculateMaxBudget(config);
  config.fitness = ReadFitnesses(root.get_child("fitnesses"),
                                 config.max_fitness, config.max_budget);
  config.joy = ReadEnjoyment(root.get_child("enjoyment"), config.max_shocks);
  config.shock_prob = ReadProb(root.get_child("probability"));
  config.shock_income_size = root.get<int>("shock_income_size");
  config.shock_count_size = root.get<int>("shock_count_size");
  config.insurance = ReadInsurance(root.get_child("insurance"), config);
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

}  // namespace configuration
}  // namespace healthcare
