#include "dp/decision_cache.h"
#include "healthcare/decision.h"
#include "healthcare/decision_evaluator.h"

#include <algorithm>
#include <numeric>
#include <vector>

namespace dp {

using namespace healthcare;

DecisionCache::DecisionCache(Configuration config, DecisionEvaluator eval, int age)
    : config_(config),
      eval_(eval),
      age_(age),
      counts_(BuildCounts()),
      decisions_(BuildDecisions()) {}

std::vector<std::vector<std::vector<int>>> DecisionCache::BuildCounts() const {
  std::vector<std::vector<std::vector<int>>> counts;
  counts.reserve(config_.max_shocks);
  for (int shocks = 0; shocks <= config_.max_shocks; ++shocks) {
    std::vector<std::vector<int>> sub_counts;
    for (int fit = 0; fit <= config_.max_fitness; ++fit) {
      sub_counts.push_back(BuildShocksCounts(shocks, fit));
    }
    counts.push_back(sub_counts);
  }
  return counts;
}

std::vector<int> DecisionCache::BuildShocksCounts(int shocks, int fit) const {
  int max_b = config_.max_budget;
  std::vector<int> counts(max_b + 1, 1);
  for (int budget = 0; budget <= max_b; ++budget) {
    counts[budget] = NOptionsExactBudget(shocks, fit, budget);
  }
  std::partial_sum(counts.begin(), counts.end(), counts.begin());
  return counts;
}

int DecisionCache::NOptionsExactBudget(int shocks, int fitness,
                                       int budget) const {
  int insurance_cost = config_.insurance->GetPrice(age_, shocks, fitness);
  int min_fitness = config_.fitness->GetFitness(fitness, 0);
  int max_fitness = config_.fitness->GetFitness(fitness, budget);
  int max_fitness_ins =
      insurance_cost <= budget
          ? config_.fitness->GetFitness(fitness, budget - insurance_cost)
          : -1;
  int n_options = 0;

  // Ensure these fitness levels are actually attainable
  for (int f = min_fitness; f <= max_fitness_ins; ++f) {
    if (config_.fitness->GetFitnessCost(fitness, f) <= budget) {
      n_options += 2;
    }
  }
  for (int f = max_fitness_ins + 1; f <= max_fitness; ++f) {
    if (config_.fitness->GetFitnessCost(fitness, f) <= budget) {
      n_options += 1;
    }
  }

  return n_options;
}

std::vector<std::vector<std::vector<DecisionResults>>>
DecisionCache::BuildDecisions() const {
  std::vector<std::vector<std::vector<DecisionResults>>> decs;
  for (int shocks = 0; shocks <= config_.max_shocks; ++shocks) {
    std::vector<std::vector<DecisionResults>> sub_decs;
    for (int fit = 0; fit <= config_.max_fitness; ++fit) {
      sub_decs.push_back(BuildShocksDecisions(shocks, fit));
    }
    decs.push_back(sub_decs);
  }
  return decs;
}

std::vector<DecisionResults> DecisionCache::BuildShocksDecisions(
    int shocks, int fitness) const {
  std::vector<Decision> decs;
  int insurance_cost = config_.insurance->GetPrice(age_, shocks, fitness);
  int min_fitness = config_.fitness->GetFitness(fitness, 0);
  int max_fitness = config_.fitness->GetFitness(fitness, config_.max_budget);

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

  std::stable_sort(decs.begin(), decs.end(), [](Decision dec, Decision dec2) {
    return TotalSpending(dec) < TotalSpending(dec2);
  });

  std::vector<DecisionResults> res;
  std::transform(
      decs.begin(), decs.end(), std::back_inserter(res),
      [this, shocks, fitness](const Decision& dec) {
        return eval_.GetDecisionResults({age_, shocks, fitness, 0}, dec);
      });
  return res;
}

}  // namespace dp
