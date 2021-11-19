#ifndef HEALTHCARE_DECISION_EVALUATOR_H_
#define HEALTHCARE_DECISION_EVALUATOR_H_

#include <algorithm>
#include <iostream>
#include <vector>

#include "healthcare/configuration.h"
#include "healthcare/decision.h"
#include "healthcare/decision_results.h"
#include "healthcare/period_result.h"
#include "healthcare/person.h"

namespace healthcare {

class DecisionEvaluator {
 public:
  DecisionEvaluator(Configuration config, int age)
      : config_(config), age_(age) {
    std::cout << config_.shock_prob(1, 0, 75) << std::endl;
    Precalculate();
    std::cout << config_.shock_prob(1, 0, 75) << std::endl;
  }
  DecisionResults GetDecisionResults(Person state, const Decision& dec) const;

 private:
  PeriodResult ApplyDecision(Person state, const Decision& dec) const;
  PeriodResult ApplyShock(PeriodResult, const Decision& dec) const;
  PeriodResult ApplyNoShock(PeriodResult) const;
  void Precalculate();
  std::vector<std::vector<std::vector<float>>> utility_;
  std::vector<std::vector<std::vector<float>>> joy_;
  std::vector<std::vector<float>> shock_prob_;
  std::vector<std::vector<float>> shock_prob_subj_;
  std::vector<std::vector<float>> no_shock_prob_subj_;
  std::vector<std::vector<float>> death_prob_;
  std::vector<std::vector<float>> no_death_prob_subj_;
  std::vector<std::vector<std::vector<int>>> fitness_;
  Configuration config_;
  int age_;
};

}  // namespace healthcare

#endif  // HEALTHCARE_DECISION_EVALUATOR_H_
