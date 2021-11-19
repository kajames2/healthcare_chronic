#ifndef HEALTHCARE_PERIOD_RESULT_H_
#define HEALTHCARE_PERIOD_RESULT_H_

#include <ostream>

#include "healthcare/person.h"

namespace healthcare {

struct PeriodResult {
  Person person;
  float joy;
  float probability;
  float subj_prob;
  float shock_prob;
  float subj_shock_prob;
  float subj_no_shock_prob;
  float death_prob;
  float subj_no_death_prob;
  int spending;
  float immediate_utility;
  float future_utility;
  float utility;
};

std::ostream& operator<<(std::ostream& os, const PeriodResult& pr);

}  // namespace healthcare

#endif  // HEALTHCARE_PERIOD_RESULT_H_
