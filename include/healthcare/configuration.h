#ifndef HEALTHCARE_CONFIGURATION_H_
#define HEALTHCARE_CONFIGURATION_H_

#include <functional>
#include <memory>
#include <string>

#include "healthcare/insurance.h"

namespace healthcare {

struct Configuration {
  int max_age;
  int max_fitness;
  int max_shocks;
  int max_savings;
  int min_savings;
  int max_budget;
  float min_debt_payment;
  float discount;
  std::function<int(int age, int shocks, int fitness)> job;
  std::function<int(int age, int shocks, int fitness, int investments)> fitness;
  std::function<double(int age, int shocks, int fitness, int investments)> joy;
  std::function<double(int age, int shocks, int fitness, double joy)> utility;
  std::function<float(int age, int shocks, int fitness)> shock_prob;
  std::function<float(int age, int shocks, int fitness, float prob)> subj_prob;
  std::shared_ptr<const healthcare::Insurance> insurance;
  int shock_income_size;
  int shock_count_size;
};

Configuration ReadConfigurationFile(std::string filename);

}  // namespace healthcare

#endif  // HEALTHCARE_CONFIGURATION_H_
