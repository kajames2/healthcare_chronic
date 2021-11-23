#ifndef DP_DECISION_CACHE_H_
#define DP_DECISION_CACHE_H_

#include <iostream>
#include <vector>

#include "healthcare/configuration.h"
#include "healthcare/decision.h"
#include "healthcare/decision_evaluator.h"
#include "healthcare/person.h"

namespace dp {

class DecisionCache {
 public:
  DecisionCache(std::shared_ptr<const healthcare::Configuration> config,
                const healthcare::DecisionEvaluator& eval, unsigned int age);
  typename std::vector<healthcare::DecisionResults>::const_iterator begin(
      unsigned int shocks, unsigned int fitness, unsigned int budget) const;
  typename std::vector<healthcare::DecisionResults>::const_iterator end(
      unsigned int shocks, unsigned int fitness, unsigned int budget) const;
  unsigned int GetDecisionCount(unsigned int shocks, unsigned int fitness,
                                unsigned int budget) const;

 private:
  std::shared_ptr<const healthcare::Configuration> config_;
  unsigned int age_;
  std::vector<std::vector<std::vector<unsigned int>>> counts_;
  std::vector<std::vector<std::vector<healthcare::DecisionResults>>> decisions_;

  void BuildCache(const healthcare::DecisionEvaluator& eval);
  void BuildShockFitnessCache(unsigned int shocks, unsigned int fitness,
                              const healthcare::DecisionEvaluator& eval);
};

}  // namespace dp

#endif  // DP_DECISION_CACHE_H_
