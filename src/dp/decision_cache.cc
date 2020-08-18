#include "dp/decision_cache.h"
#include "healthcare/decision.h"
#include "healthcare/decision_evaluator.h"

#include <omp.h>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

namespace dp {

using ::healthcare::Decision;

DecisionCache::DecisionCache(healthcare::Configuration config,
                             healthcare::DecisionEvaluator eval, int age)
    : config_(std::move(config)),
      eval_(std::move(eval)),
      age_(age),
      counts_(config_.max_shocks + 1),
      decisions_(config_.max_shocks + 1) {
  BuildCache();
}

typename std::vector<healthcare::DecisionResults>::const_iterator
DecisionCache::begin(int shocks, int fitness, int budget) const {
  if (budget > config_.max_savings) {
    return decisions_[shocks][fitness].begin() +
           counts_[shocks][fitness][budget - config_.max_savings - 1];
  }
  return decisions_[shocks][fitness].begin();
}

typename std::vector<healthcare::DecisionResults>::const_iterator
DecisionCache::end(int shocks, int fitness, int budget) const {
  return decisions_[shocks][fitness].begin() + counts_[shocks][fitness][budget];
}

int DecisionCache::GetDecisionCount(int shocks, int fitness, int budget) const {
  if (budget > config_.max_savings) {
    return counts_[shocks][fitness][budget] -
           counts_[shocks][fitness][budget - config_.max_savings - 1];
  }
  return counts_[shocks][fitness][budget];
}

void DecisionCache::BuildCache() {
  for (int shocks = 0; shocks <= config_.max_shocks; ++shocks) {
    for (int fit = 0; fit <= config_.max_fitness; ++fit) {
      BuildShockFitnessCache(shocks, fit);
    }
  }
}

void DecisionCache::BuildShockFitnessCache(int shocks, int fitness) {
  std::vector<Decision> decs;

  // // You can always purchase insurance (and nothing else)
  // decs.push_back(Decision{0, 0, insurance_cost});

  int prev_fit = -1;
  for (int fit_cost = 0; fit_cost <= config_.max_budget; ++fit_cost) {
    int fit = config_.fitness(age_, shocks, fitness, fit_cost);
    if (fit == prev_fit) {
      continue;
    }
    prev_fit = fit;
    int rem_budget = config_.max_budget - fit_cost;
    int insurance_cost = config_.insurance->GetPrice(age_, shocks, fit);

    for (int joy_spending = 0; joy_spending <= rem_budget; ++joy_spending) {
      decs.push_back(Decision{fit_cost, joy_spending, 0, false});
    }
    rem_budget -= insurance_cost;
    for (int joy_spending = 0; joy_spending <= rem_budget; ++joy_spending) {
      decs.push_back(Decision{fit_cost, joy_spending, insurance_cost, true});
    }
  }
  // // Sort all except the guaranteed insurance purchase
  // std::stable_sort(decs.begin() + 1, decs.end(),
  //                  [](Decision dec, Decision dec2) {
  //                    return TotalSpending(dec) < TotalSpending(dec2);
  //                  });
  std::stable_sort(decs.begin(), decs.end(), [](Decision dec, Decision dec2) {
    return TotalSpending(dec) < TotalSpending(dec2);
  });

  std::vector<int> counts(config_.max_budget + 1, 0);
  // Account for guaranteed insurance purchase option
  // counts[0] = 1;
  // for (auto dec = decs.begin() + 1; dec != decs.end(); ++dec) {
  for (auto dec = decs.begin(); dec != decs.end(); ++dec) {
    ++counts[TotalSpending(*dec)];
  }

  std::partial_sum(counts.begin(), counts.end(), counts.begin());

  std::vector<healthcare::DecisionResults> res(decs.size());
  //  #pragma omp parallel for
  for (int i = 0; i < decs.size(); ++i) {
    res[i] = eval_.GetDecisionResults({age_, shocks, fitness, 0}, decs[i]);
  }
  //  std::vector<healthcare::DecisionResults> res;
  //  std::transform(
  //      decs.begin(), decs.end(), std::back_inserter(res),
  //      [this, shocks, fitness](const Decision& dec) {
  //        return eval_.GetDecisionResults({age_, shocks, fitness, 0}, dec);
  //      });
  decisions_[shocks].push_back(res);
  counts_[shocks].push_back(counts);
}

}  // namespace dp
