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
  res.immediate_utility =
      utility_[state.shocks][state.fitness][dec.joy_spending];
  res.spending = TotalSpending(dec);
  res.shock_prob = shock_prob_[res.person.shocks][res.person.fitness];
  res.subj_shock_prob = shock_prob_subj_[res.person.shocks][res.person.fitness];
  res.subj_no_shock_prob = no_shock_prob_subj_[res.person.shocks][res.person.fitness];
  res.future_utility = 0;
  res.utility = 0;
  ++res.person.age;
  return res;
}

PeriodResult DecisionEvaluator::ApplyNoShock(PeriodResult res) const {
  res.probability = 1 - res.shock_prob;
  res.subj_prob = res.subj_no_shock_prob;
  res.person.cash -= res.spending;
  return res;
}

PeriodResult DecisionEvaluator::ApplyShock(PeriodResult res,
                                           const Decision& dec) const {
  res.probability = res.shock_prob;
  res.subj_prob = res.subj_shock_prob;
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
    std::vector<std::vector<float>> sub_util;
    std::vector<std::vector<float>> sub_joy;
    std::vector<float> sub_prob;
    std::vector<float> sub_prob_shock_subj;
    std::vector<float> sub_prob_noshock_subj;
    std::vector<std::vector<int>> sub_fit;
    for (int fitness = 0; fitness <= config_.max_fitness; ++fitness) {
      std::vector<float> sub_sub_util;
      std::vector<float> sub_sub_joy;
      for (int joy_spend = 0; joy_spend <= config_.max_budget; ++joy_spend) {
        float joy = config_.joy(age_, shocks, fitness, joy_spend);
        sub_sub_joy.push_back(joy);
        sub_sub_util.push_back(config_.utility(age_, shocks, fitness, joy));
      }
      sub_joy.push_back(sub_sub_joy);
      sub_util.push_back(sub_sub_util);
      std::vector<int> sub_sub_fit;
      for (int fit_spend = 0; fit_spend <= config_.max_budget; ++fit_spend) {
        sub_sub_fit.push_back(
            config_.fitness(age_, shocks, fitness, fit_spend));
      }
      sub_fit.push_back(sub_sub_fit);
      float shock_prob = config_.shock_prob(age_, shocks, fitness);
      sub_prob.push_back(shock_prob);
      sub_prob_shock_subj.push_back(config_.subj_prob(age_, shocks, fitness, shock_prob));
      sub_prob_noshock_subj.push_back(
          config_.subj_prob(age_, shocks, fitness, 1 - shock_prob));
    }
    joy_.push_back(sub_joy);
    utility_.push_back(sub_util);
    shock_prob_.push_back(sub_prob);
    shock_prob_subj_.push_back(sub_prob_shock_subj);
    no_shock_prob_subj_.push_back(sub_prob_noshock_subj);
    fitness_.push_back(sub_fit);
  }
}

}  // namespace healthcare
