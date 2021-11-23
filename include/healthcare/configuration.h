#ifndef HEALTHCARE_CONFIGURATION_H_
#define HEALTHCARE_CONFIGURATION_H_

#include <functional>
#include <memory>
#include <string>

#include "healthcare/fitness_func.h"
#include "healthcare/insurance.h"
#include "healthcare/job_func.h"
#include "healthcare/joy_func.h"
#include "healthcare/prob_dependent_func.h"
#include "healthcare/prob_func.h"
#include "healthcare/utility_func.h"

namespace healthcare {

class Configuration {
 public:
  Configuration(std::string filename);
  unsigned int max_age;
  unsigned int max_fitness;
  unsigned int max_shocks;
  unsigned int max_savings;
  int min_savings;
  unsigned int max_budget;
  bool save_pessimal;
  float min_debt_payment;
  float discount;
  std::shared_ptr<const healthcare::Insurance> insurance;
  unsigned int shock_income_size;
  unsigned int shock_count_size;
  int job(unsigned int age, unsigned int shocks, unsigned int fitness) const {
    return (*job_)(age, shocks, fitness);
  }
  unsigned int fitness(unsigned int age, unsigned int shocks,
                       unsigned int fitness, unsigned int investment) const {
    return (*fitness_)(age, shocks, fitness, investment);
  }
  double joy(unsigned int age, unsigned int shocks, unsigned int fitness,
             unsigned int investment) const {
    return (*joy_)(age, shocks, fitness, investment);
  }
  double utility(unsigned int age, unsigned int shocks, unsigned int fitness,
                 float joy) const {
    if (!utility_) {
      return static_cast<double>(joy);
    }
    return (*utility_)(age, shocks, fitness, joy);
  }
  float shock_prob(unsigned int age, unsigned int shocks,
                   unsigned int fitness) const {
    return (*shock_prob_)(age, shocks, fitness);
  }
  float subj_prob(unsigned int age, unsigned int shocks, unsigned int fitness,
                  float prob) const {
    if (!subj_prob_) {
      return prob;
    }
    return (*subj_prob_)(age, shocks, fitness, prob);
  }
  float death_prob(unsigned int age, unsigned int shocks, unsigned int fitness,
                   float prob) const {
    if (!death_prob_) {
      return 0;
    }
    return (*death_prob_)(age, shocks, fitness, prob);
  }

 private:
  std::unique_ptr<JobFunc> job_;
  std::unique_ptr<FitnessFunc> fitness_;
  std::unique_ptr<JoyFunc> joy_;
  std::unique_ptr<UtilityFunc> utility_;
  std::unique_ptr<ProbFunc> shock_prob_;
  std::unique_ptr<ProbDepFunc> subj_prob_;
  std::unique_ptr<ProbDepFunc> death_prob_;
};

}  // namespace healthcare

#endif  // HEALTHCARE_CONFIGURATION_H_
