#include "dp/storage.h"

#include <cassert>
#include <ostream>
#include <vector>

#include "healthcare/configuration.h"
#include "healthcare/person.h"

namespace dp {

Storage::Storage(const healthcare::Configuration& c)
    : config_(c),
      n_elements_((c.max_shocks + 1) * (c.max_fitness + 1) *
                  (c.max_savings - c.min_savings + 1)) {
  results_ = std::vector<std::vector<std::vector<healthcare::DecisionResults>>>(
      c.max_shocks + 1);
  values_ = std::vector<std::vector<std::vector<float>>>(c.max_shocks + 1);
  for (int i = 0; i <= c.max_shocks; ++i) {
    results_[i].resize(c.max_fitness + 1);
    values_[i].resize(c.max_fitness + 1);
    for (int j = 0; j <= c.max_fitness; ++j) {
      results_[i][j].resize(c.max_savings - c.min_savings + 1);
      values_[i][j].resize(c.max_savings - c.min_savings + 1);
    }
  }
}

int Storage::GetIndex(const healthcare::Person& state) const {
  assert(IsValidState(state));
  static int row_size = config_.max_savings - config_.min_savings + 1;
  static int sub_table_size = (config_.max_fitness + 1) * row_size;
  return (state.shocks * sub_table_size) + (state.fitness * row_size) +
         (state.cash - config_.min_savings);
}

bool Storage::IsValidState(const healthcare::Person& state) const {
  return state.fitness >= 0 && state.fitness <= config_.max_fitness &&
         state.shocks >= 0 && state.shocks <= config_.max_shocks &&
         state.cash >= config_.min_savings && state.cash <= config_.max_savings;
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
  int age_size = GetPrintSize(s.config_.max_age);
  int shocks_size = GetPrintSize(s.config_.max_shocks);
  int fitness_size = GetPrintSize(s.config_.max_fitness);
  int savings_size = std::max(GetPrintSize(s.config_.max_savings),
                              GetPrintSize(s.config_.min_savings));
  int spending_size = GetPrintSize(s.config_.max_budget);
  for (int shocks = 0; shocks <= s.config_.max_shocks; ++shocks) {
    for (int fitness = 0; fitness <= s.config_.max_fitness; ++fitness) {
      for (int cash = s.config_.min_savings; cash <= s.config_.max_savings;
           ++cash) {
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
            << opt.result.probability << ',' << std::setprecision(2)
            << std::setw(6) << opt.result.joy << "," << std::setprecision(2)
            << std::setw(6) << opt.result.future_value << ","
            << std::setprecision(2) << std::setw(6) << opt.result.value << "\n";

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
            << opt.result_shock.probability << ',' << std::setprecision(2)
            << std::setw(6) << opt.result_shock.joy << ","
            << std::setprecision(2) << std::setw(6)
            << opt.result_shock.future_value << "," << std::setprecision(2)
            << std::setw(6) << opt.result_shock.value;

        // out << state << "," << opt.decision << "," << opt.result << '\n';
        // out << state << ',' << opt.decision << ',' << opt.result_shock;
        if (shocks != s.config_.max_shocks ||
            fitness != s.config_.max_fitness || cash != s.config_.max_savings) {
          out << '\n';
        }
      }
    }
    out << std::flush;
  }
  return out;
}

}  // namespace dp
