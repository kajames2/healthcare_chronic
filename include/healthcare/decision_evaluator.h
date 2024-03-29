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
  DecisionEvaluator(std::shared_ptr<const Configuration> config,
                    unsigned int age);
  DecisionResults GetDecisionResults(Person state, const Decision& dec) const;

 private:
  PeriodResult ApplyDecision(Person state, const Decision& dec) const;
  PeriodResult ApplyShock(PeriodResult, const Decision& dec) const;
  PeriodResult ApplyNoShock(PeriodResult) const;
  std::shared_ptr<const Configuration> config_;
  unsigned int age_;
  std::vector<std::vector<std::vector<float>>> utility_;
  std::vector<std::vector<std::vector<float>>> joy_;
  std::vector<std::vector<float>> shock_prob_;
  std::vector<std::vector<float>> shock_prob_subj_;
  std::vector<std::vector<float>> no_shock_prob_subj_;
  std::vector<std::vector<float>> death_prob_;
  std::vector<std::vector<float>> no_death_prob_subj_;
  std::vector<std::vector<std::vector<unsigned int>>> fitness_;
  void Precalculate();
};

}  // namespace healthcare

#endif  // HEALTHCARE_DECISION_EVALUATOR_H_
