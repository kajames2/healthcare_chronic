#ifndef HEALTHCARE_CONFIGURATION_H_
#define HEALTHCARE_CONFIGURATION_H_

#include <memory>
#include <string>

#include "healthcare/fitness.h"
#include "healthcare/insurance.h"
#include "healthcare/job.h"
#include "healthcare/joy.h"
#include "healthcare/modulator.h"
#include "healthcare/probability.h"

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
  std::shared_ptr<const healthcare::Job> job;
  std::shared_ptr<const healthcare::Fitness> fitness;
  std::shared_ptr<const healthcare::Joy> joy;
  std::shared_ptr<const healthcare::Probability> shock_prob;
  std::shared_ptr<const healthcare::Insurance> insurance;
  int shock_income_size;
  int shock_count_size;
};

Configuration ReadConfigurationFile(std::string filename);

}  // namespace healthcare

#endif  // HEALTHCARE_CONFIGURATION_H_
