#ifndef _HEALTHCAREDP_DECISION_CACHE_H_
#define _HEALTHCAREDP_DECISION_CACHE_H_

#include <iostream>
#include <vector>

#include "healthcare/configuration.h"
#include "healthcare/decision.h"
#include "healthcare/decision_evaluator.h"
#include "healthcare/fitness.h"
#include "healthcare/person.h"

namespace dp {

class DecisionCache {
 public:
  DecisionCache(healthcare::Configuration config,
                healthcare::DecisionEvaluator eval, int age);

  typename std::vector<healthcare::DecisionResults>::const_iterator begin(
      int shocks, int fitness, int budget) const {
    if (budget > config_.max_savings) {
      return decisions_[shocks][fitness].begin() +
             counts_[shocks][fitness][budget - config_.max_savings - 1];
    }
    return decisions_[shocks][fitness].begin();
  }

  typename std::vector<healthcare::DecisionResults>::const_iterator end(
      int shocks, int fitness, int budget) const {
    return decisions_[shocks][fitness].begin() +
           counts_[shocks][fitness][budget];
  }

  int GetDecisionCount(int shocks, int fitness, int budget) const {
    if (budget > config_.max_savings) {
      return counts_[shocks][fitness][budget] -
             counts_[shocks][fitness][budget - config_.max_savings - 1];
    }
    return counts_[shocks][fitness][budget];
  }

 private:
  const healthcare::Configuration config_;
  const healthcare::DecisionEvaluator eval_;
  int age_;
  const std::vector<std::vector<std::vector<int>>> counts_;
  const std::vector<std::vector<std::vector<healthcare::DecisionResults>>>
      decisions_;

  std::vector<std::vector<std::vector<int>>> BuildCounts() const;
  std::vector<int> BuildShocksCounts(int shocks, int fitness) const;
  int NOptionsExactBudget(int conds, int fitness, int budget) const;
  std::vector<std::vector<std::vector<healthcare::DecisionResults>>>
  BuildDecisions() const;
  std::vector<healthcare::DecisionResults> BuildShocksDecisions(
      int shocks, int fitness) const;
};

}  // namespace dp

#endif  // _HEALTHCAREDP_DECISION_CACHE_H_
