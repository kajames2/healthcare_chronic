#ifndef _HEALTHCARE_PERIOD_RESULT_H_
#define _HEALTHCARE_PERIOD_RESULT_H_

#include "healthcare/person.h"

#include <ostream>

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

#endif  // _HEALTHCARE_PERIOD_RESULT_H_
