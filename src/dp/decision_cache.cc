#include "dp/decision_cache.h"
#include "healthcare/decision.h"
#include "healthcare/decision_evaluator.h"

#include <algorithm>
#include <numeric>
#include <vector>

namespace dp {

using namespace healthcare;

DecisionCache::DecisionCache(Configuration config, DecisionEvaluator eval,
                             int age)
    : config_(std::move(config)),
      eval_(std::move(eval)),
      age_(age),
      counts_(config_.max_shocks + 1),
      decisions_(config_.max_shocks + 1) {
  BuildCache();
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
  int insurance_cost = config_.insurance->GetPrice(age_, shocks, fitness);
  int min_fitness = config_.fitness->GetFitness(fitness, 0);
  int max_fitness = config_.fitness->GetFitness(fitness, config_.max_budget);

  // You can always purchase insurance (and nothing else)
  decs.push_back(Decision{0, 0, insurance_cost});

  for (int fit = min_fitness; fit <= max_fitness; ++fit) {
    int fit_cost = config_.fitness->GetFitnessCost(fitness, fit);
    int rem_budget = config_.max_budget - fit_cost;

    for (int joy_spending = 0; joy_spending <= rem_budget; ++joy_spending) {
      decs.push_back(Decision{fit_cost, joy_spending, 0});
    }
    rem_budget -= insurance_cost;
    for (int joy_spending = 0; joy_spending <= rem_budget; ++joy_spending) {
      decs.push_back(Decision{fit_cost, joy_spending, insurance_cost});
    }
  }

  // Sort all except the guaranteed insurance purchase
  std::stable_sort(decs.begin() + 1, decs.end(),
                   [](Decision dec, Decision dec2) {
                     return TotalSpending(dec) < TotalSpending(dec2);
                   });

  std::vector<int> counts(config_.max_budget + 1, 0);
  // Account for guaranteed insurance purchase option
  counts[0] = 1;
  for (auto dec = decs.begin() + 1; dec != decs.end(); ++dec) {
    ++counts[TotalSpending(*dec)];
  }
  std::partial_sum(counts.begin(), counts.end(), counts.begin());

  std::vector<DecisionResults> res;
  std::transform(
      decs.begin(), decs.end(), std::back_inserter(res),
      [this, shocks, fitness](const Decision& dec) {
        return eval_.GetDecisionResults({age_, shocks, fitness, 0}, dec);
      });

  decisions_[shocks].push_back(res);
  counts_[shocks].push_back(counts);
}

}  // namespace dp
