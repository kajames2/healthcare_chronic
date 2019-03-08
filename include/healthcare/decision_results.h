#ifndef HEALTHCARE_DECISION_RESULTS_H_
#define HEALTHCARE_DECISION_RESULTS_H_

#include "healthcare/decision.h"
#include "healthcare/person.h"
#include "healthcare/period_result.h"

namespace healthcare {

struct DecisionResults {
  Decision decision;
  PeriodResult result;
  PeriodResult result_shock;
  float value;
};

}  // namespace healthcare

#endif  // HEALTHCARE_DECISION_RESULTS_H_
