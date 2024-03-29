#include "healthcare/decision_evaluator.h"

#include <algorithm>
#include <iostream>
#include <vector>

namespace healthcare {

DecisionEvaluator::DecisionEvaluator(
    std::shared_ptr<const Configuration> config, unsigned int age)
    : config_(config), age_(age) {
  Precalculate();
}

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
  res.subj_no_shock_prob =
      no_shock_prob_subj_[res.person.shocks][res.person.fitness];
  res.death_prob = death_prob_[res.person.shocks][res.person.fitness];
  res.subj_no_death_prob =
      no_death_prob_subj_[res.person.shocks][res.person.fitness];
  res.future_utility = 0;
  res.utility = 0;
  ++res.person.age;
  return res;
}

PeriodResult DecisionEvaluator::ApplyNoShock(PeriodResult res) const {
  res.probability = 1 - res.shock_prob;
  res.subj_prob = res.subj_no_shock_prob;
  res.person.cash -= static_cast<int>(res.spending);
  return res;
}

PeriodResult DecisionEvaluator::ApplyShock(PeriodResult res,
                                           const Decision& dec) const {
  res.probability = res.shock_prob;
  res.subj_prob = res.subj_shock_prob;
  res.person.shocks += config_->shock_count_size;
  res.person.shocks = std::min(config_->max_shocks, res.person.shocks);
  if (!dec.buy_insurance) {
    res.spending += config_->shock_income_size;
  }
  res.person.cash -= static_cast<int>(res.spending);
  return res;
}

void DecisionEvaluator::Precalculate() {
  for (unsigned int shocks = 0; shocks <= config_->max_shocks; ++shocks) {
    std::vector<std::vector<float>> sub_util;
    std::vector<std::vector<float>> sub_joy;
    std::vector<float> sub_prob;
    std::vector<float> sub_prob_shock_subj;
    std::vector<float> sub_prob_noshock_subj;
    std::vector<float> sub_prob_death;
    std::vector<float> sub_prob_no_death_subj;
    std::vector<std::vector<unsigned int>> sub_fit;
    for (unsigned int fitness = 0; fitness <= config_->max_fitness; ++fitness) {
      std::vector<float> sub_sub_util;
      std::vector<float> sub_sub_joy;
      for (unsigned int joy_spend = 0;
           joy_spend <= static_cast<unsigned int>(config_->max_budget);
           ++joy_spend) {
        float joy =
            static_cast<float>(config_->joy(age_, shocks, fitness, joy_spend));
        sub_sub_joy.push_back(joy);
        sub_sub_util.push_back(config_->utility(age_, shocks, fitness, joy));
      }
      sub_joy.push_back(sub_sub_joy);
      sub_util.push_back(sub_sub_util);
      std::vector<unsigned int> sub_sub_fit;
      for (unsigned int fit_spend = 0;
           fit_spend <= static_cast<unsigned int>(config_->max_budget);
           ++fit_spend) {
        sub_sub_fit.push_back(
            config_->fitness(age_, shocks, fitness, fit_spend));
      }
      sub_fit.push_back(sub_sub_fit);

      float shock_prob = config_->shock_prob(age_, shocks, fitness);
      float death_prob = config_->death_prob(age_, shocks, fitness, shock_prob);
      float shock_prob_adj =
          death_prob == 1 ? 0 : (shock_prob - death_prob) / (1 - death_prob);

      sub_prob.push_back(shock_prob_adj);
      sub_prob_shock_subj.push_back(
          config_->subj_prob(age_, shocks, fitness, shock_prob_adj));
      sub_prob_noshock_subj.push_back(
          config_->subj_prob(age_, shocks, fitness, 1 - shock_prob_adj));

      sub_prob_death.push_back(death_prob);
      sub_prob_no_death_subj.push_back(
          config_->subj_prob(age_, shocks, fitness, 1 - death_prob));
    }
    joy_.push_back(sub_joy);
    utility_.push_back(sub_util);
    shock_prob_.push_back(sub_prob);
    shock_prob_subj_.push_back(sub_prob_shock_subj);
    no_shock_prob_subj_.push_back(sub_prob_noshock_subj);
    death_prob_.push_back(sub_prob_death);
    no_death_prob_subj_.push_back(sub_prob_no_death_subj);
    fitness_.push_back(sub_fit);
  }
}

}  // namespace healthcare
