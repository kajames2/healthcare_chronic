#include "healthcare/decision_evaluator.h"

#include <algorithm>
#include <vector>

namespace healthcare {

DecisionResults DecisionEvaluator::GetDecisionResults(
    Person state, const Decision& dec) const {
  auto res = ApplyDecision(state, dec);
  auto res_no_shock = ApplyNoShock(res);
  auto res_shock = ApplyShock(res, dec);
  return {dec, res_no_shock, res_shock, 0};
}

PeriodResult DecisionEvaluator::ApplyDecision(Person state,
                                              const Decision& dec) const {
  state.fitness = fitness_[state.shocks][state.fitness][dec.fitness_spending];
  PeriodResult res;
  res.person = state;
  res.joy = joy_[state.shocks][state.fitness][dec.joy_spending];
  res.spending = TotalSpending(dec);
  res.future_value = 0;
  res.value = 0;
  ++res.person.age;
  return res;
}

PeriodResult DecisionEvaluator::ApplyNoShock(PeriodResult res) const {
  res.probability = 1 - shock_prob_[res.person.shocks][res.person.fitness];
  res.person.cash -= res.spending;
  return res;
}

PeriodResult DecisionEvaluator::ApplyShock(PeriodResult res,
                                           const Decision& dec) const {
  res.probability = shock_prob_[res.person.shocks][res.person.fitness];
  res.person.shocks += config_.shock_count_size;
  res.person.shocks = std::min(config_.max_shocks, res.person.shocks);
  if (!dec.buy_insurance) {
    res.spending += config_.shock_income_size;
  }
  res.person.cash -= res.spending;
  return res;
}

void DecisionEvaluator::Precalculate() {
  for (int shocks = 0; shocks <= config_.max_shocks; ++shocks) {
    std::vector<std::vector<float>> sub_joy;
    std::vector<float> sub_prob;
    std::vector<std::vector<int>> sub_fit;
    for (int fitness = 0; fitness <= config_.max_fitness; ++fitness) {
      std::vector<float> sub_sub_joy;
      for (int joy_spend = 0; joy_spend <= config_.max_budget; ++joy_spend) {
        sub_sub_joy.push_back(config_.joy(age_, shocks, fitness, joy_spend));
      }
      sub_joy.push_back(sub_sub_joy);
      std::vector<int> sub_sub_fit;
      for (int fit_spend = 0; fit_spend <= config_.max_budget; ++fit_spend) {
        sub_sub_fit.push_back(
            config_.fitness(age_, shocks, fitness, fit_spend));
      }
      sub_fit.push_back(sub_sub_fit);
      sub_prob.push_back(config_.shock_prob(age_, shocks, fitness));
    }
    joy_.push_back(sub_joy);
    shock_prob_.push_back(sub_prob);
    fitness_.push_back(sub_fit);
  }
}

}  // namespace healthcare
