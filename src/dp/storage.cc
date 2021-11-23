#include "dp/storage.h"

#include <cassert>
#include <iostream>
#include <vector>

#include "healthcare/configuration.h"
#include "healthcare/person.h"

namespace dp {

Storage::Storage(std::shared_ptr<const healthcare::Configuration> c)
    : config_(c),
      n_elements_((c->max_shocks + 1) * (c->max_fitness + 1) *
                  (CashDiff(static_cast<int>(c->max_savings)) + 1)) {
  results_ = std::vector<std::vector<std::vector<healthcare::DecisionResults>>>(
      c->max_shocks + 1);
  values_ = std::vector<std::vector<std::vector<float>>>(c->max_shocks + 1);
  for (unsigned int i = 0; i <= c->max_shocks; ++i) {
    results_[i].resize(c->max_fitness + 1);
    values_[i].resize(c->max_fitness + 1);
    for (unsigned int j = 0; j <= c->max_fitness; ++j) {
      results_[i][j].resize(CashDiff(static_cast<int>(c->max_savings)) + 1);
      values_[i][j].resize(CashDiff(static_cast<int>(c->max_savings)) + 1);
    }
  }
}

unsigned int Storage::GetIndex(const healthcare::Person& state) const {
  assert(IsValidState(state));
  static unsigned int row_size =
      CashDiff(static_cast<int>(config_->max_savings)) + 1;
  static unsigned int sub_table_size = (config_->max_fitness + 1) * row_size;
  return (state.shocks * sub_table_size) + (state.fitness * row_size) +
         (CashDiff(state.cash));
}

bool Storage::IsValidState(const healthcare::Person& state) const {
  return state.fitness <= config_->max_fitness &&
         state.shocks <= config_->max_shocks &&
         state.cash >= config_->min_savings &&
         static_cast<unsigned int>(state.cash) <= config_->max_savings;
}

int GetPrintSize(int num) {
  int size = 1;
  if (num < 0) {
    ++size;
  }
  while (num /= 10) {
    size += 1;
  }
  return size;
}

std::ostream& operator<<(std::ostream& out, const Storage& s) {
  int age_size = GetPrintSize(static_cast<int>(s.config_->max_age));
  int shocks_size = GetPrintSize(static_cast<int>(s.config_->max_shocks));
  int fitness_size = GetPrintSize(static_cast<int>(s.config_->max_fitness));
  int savings_size =
      std::max(GetPrintSize(static_cast<int>(s.config_->max_savings)),
               GetPrintSize(s.config_->min_savings));
  int spending_size = GetPrintSize(static_cast<int>(s.config_->max_budget));
  for (unsigned int shocks = 0; shocks <= s.config_->max_shocks; ++shocks) {
    for (unsigned int fitness = 0; fitness <= s.config_->max_fitness;
         ++fitness) {
      for (int cash = s.config_->min_savings;
           cash <= static_cast<int>(s.config_->max_savings); ++cash) {
        healthcare::Person state = healthcare::Person{0, shocks, fitness, cash};
        auto opt = s.GetResult(state);
        state.age = opt.result.person.age - 1;
        out << std::setw(age_size) << state.age << "," << std::setw(shocks_size)
            << state.shocks << "," << std::setw(fitness_size) << state.fitness
            << "," << std::setw(savings_size) << state.cash << ","
            << std::setw(spending_size) << opt.decision.fitness_spending << ","
            << std::setw(spending_size) << opt.decision.joy_spending << ","
            << std::setw(spending_size) << opt.decision.insurance_spending
            << "," << std::setw(1)
            << static_cast<int>(opt.decision.buy_insurance) << ","
            << std::setw(age_size) << opt.result.person.age << ","
            << std::setw(shocks_size) << opt.result.person.shocks << ","
            << std::setw(fitness_size) << opt.result.person.fitness << ","
            << std::setw(savings_size) << opt.result.person.cash << ","
            << std::setprecision(6) << std::setw(8) << std::fixed
            << opt.result.probability << ',' << opt.result.subj_prob << ','
            << opt.result.shock_prob << ',' << opt.result.subj_shock_prob << ','
            << opt.result.subj_no_shock_prob << ',' << opt.result.death_prob
            << ',' << opt.result.subj_no_death_prob << ','
            << std::setprecision(2) << std::setw(6) << opt.result.joy << ","
            << std::setprecision(2) << std::setw(10)
            << opt.result.immediate_utility << "," << std::setprecision(2)
            << std::setw(14) << opt.result.future_utility << ","
            << std::setprecision(2) << std::setw(14) << opt.result.utility
            << "\n";

        out << std::setw(age_size) << state.age << "," << std::setw(shocks_size)
            << state.shocks << "," << std::setw(fitness_size) << state.fitness
            << "," << std::setw(savings_size) << state.cash << ","
            << std::setw(spending_size) << opt.decision.fitness_spending << ","
            << std::setw(spending_size) << opt.decision.joy_spending << ","
            << std::setw(spending_size) << opt.decision.insurance_spending
            << "," << std::setw(1)
            << static_cast<int>(opt.decision.buy_insurance) << ","
            << std::setw(age_size) << opt.result_shock.person.age << ","
            << std::setw(shocks_size) << opt.result_shock.person.shocks << ","
            << std::setw(fitness_size) << opt.result_shock.person.fitness << ","
            << std::setw(savings_size) << opt.result_shock.person.cash << ","
            << std::setprecision(6) << std::setw(8) << std::fixed
            << opt.result_shock.probability << ',' << opt.result_shock.subj_prob
            << ',' << opt.result_shock.shock_prob << ','
            << opt.result_shock.subj_shock_prob << ','
            << opt.result_shock.subj_no_shock_prob << ','
            << opt.result_shock.death_prob << ','
            << opt.result_shock.subj_no_death_prob << ','
            << std::setprecision(2) << std::setw(6) << opt.result_shock.joy
            << "," << std::setprecision(2) << std::setw(10)
            << opt.result_shock.immediate_utility << "," << std::setprecision(2)
            << std::setw(14) << opt.result_shock.future_utility << ","
            << std::setprecision(2) << std::setw(14)
            << opt.result_shock.utility;

        // out << state << "," << opt.decision << "," << opt.result << '\n';
        // out << state << ',' << opt.decision << ',' << opt.result_shock;
        if (shocks != s.config_->max_shocks ||
            fitness != s.config_->max_fitness ||
            cash != static_cast<int>(s.config_->max_savings)) {
          out << '\n';
        }
      }
    }
    out << std::flush;
  }
  return out;
}

}  // namespace dp
