#ifndef HEALTHCARE_PERIOD_RESULT_H_
#define HEALTHCARE_PERIOD_RESULT_H_

#include <ostream>

#include "healthcare/person.h"

namespace healthcare {

struct PeriodResult {
  Person person;
  float joy;
  float probability;
  int spending;
  float future_value;
  float value;
};

std::ostream& operator<<(std::ostream& os, const PeriodResult& pr);

}  // namespace healthcare

#endif  // HEALTHCARE_PERIOD_RESULT_H_
