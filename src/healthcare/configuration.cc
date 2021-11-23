#include "healthcare/configuration.h"
#include <iostream>
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
#include "configuration/subjective_probability_reader.h"
#include "configuration/utility_reader.h"
#include "exprtk.hpp"

using ::boost::property_tree::ptree;

namespace healthcare {

unsigned int CalculateMaxBudget(const Configuration& config);

Configuration::Configuration(std::string filename) {
  ptree root;
  read_json(filename, root);
  assert(root.count("max_age"));
  assert(root.count("max_fitness"));
  assert(root.count("max_shocks"));
  assert(root.count("max_savings"));
  assert(root.count("min_savings"));
  assert(root.count("job"));

  max_age = root.get<unsigned int>("max_age");
  max_fitness = root.get<unsigned int>("max_fitness");
  max_shocks = root.get<unsigned int>("max_shocks");
  max_savings = root.get<unsigned int>("max_savings");
  min_savings = root.get<int>("min_savings");
  min_debt_payment = root.get<float>("min_debt_payment");
  job_ = configuration::ReadJob(root.get_child("job"), max_age, max_shocks,
                                max_fitness);
  fitness_ = configuration::ReadFitness(root.get_child("fitness"), max_age,
                                        max_shocks, max_fitness);
  joy_ = configuration::ReadJoy(root.get_child("joy"), max_age, max_shocks,
                                max_fitness);
  shock_prob_ = configuration::ReadProb(root.get_child("probability"), max_age,
                                        max_shocks, max_fitness);
  shock_income_size = root.get<unsigned int>("shock_income_size");
  shock_count_size = root.get<unsigned int>("shock_count_size");
  insurance = configuration::ReadInsurance(root.get_child("insurance"), *this);

  max_budget = CalculateMaxBudget(*this);

  if (root.count("utility") != 0) {
    utility_ = configuration::ReadUtility(root.get_child("utility"), max_age,
                                          max_shocks, max_fitness);
  }

  if (root.count("subjective_probability") != 0) {
    subj_prob_ = configuration::ReadSubjectiveProbability(
        root.get_child("subjective_probability"), max_age, max_shocks,
        max_fitness);
  }

  if (root.count("death_prob") != 0) {
    death_prob_ = configuration::ReadSubjectiveProbability(
        root.get_child("death_probability"), max_age, max_shocks, max_fitness);
  }

  if (root.count("discount") == 0) {
    discount = 1;
  } else {
    discount = root.get<float>("discount");
  }

  if (root.count("save_pessimal") == 0) {
    save_pessimal = false;
  } else {
    save_pessimal = root.get<bool>("save_pessimal");
  }
}

unsigned int CalculateMaxBudget(const Configuration& config) {
  unsigned int max_income = 0;
  for (unsigned int age = 0; age <= config.max_age; ++age) {
    for (unsigned int shocks = 0; shocks <= config.max_shocks; ++shocks) {
      for (unsigned int fitness = 0; fitness <= config.max_fitness; ++fitness) {
        if (config.job(age, shocks, fitness) > static_cast<int>(max_income)) {
          max_income = static_cast<unsigned int>(
              std::max(0, config.job(age, shocks, fitness)));
        }
      }
    }
  }
  return max_income + config.max_savings;
}

}  // namespace healthcare
