#ifndef HEALTHCARE_DECISION_RESULTS_H_
#define HEALTHCARE_DECISION_RESULTS_H_

#include "healthcare/decision.h"
#include "healthcare/period_result.h"
#include "healthcare/person.h"

namespace healthcare {

struct DecisionResults {
  Decision decision;
  PeriodResult result;
  PeriodResult result_shock;
  float utility;
};

}  // namespace healthcare

#endif  // HEALTHCARE_DECISION_RESULTS_H_
