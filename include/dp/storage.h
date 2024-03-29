#ifndef DP_STORAGE_H_
#define DP_STORAGE_H_

#include <algorithm>
#include <iomanip>
#include <ostream>
#include <vector>

#include "healthcare/configuration.h"
#include "healthcare/decision.h"
#include "healthcare/decision_results.h"
#include "healthcare/person.h"

namespace dp {
class Storage {
 public:
  explicit Storage(std::shared_ptr<const healthcare::Configuration> config);

  void StoreResult(const healthcare::Person& state,
                   healthcare::DecisionResults res) {
    results_[state.shocks][state.fitness][CashDiff(state.cash)] = res;
    values_[state.shocks][state.fitness][CashDiff(state.cash)] = res.utility;
  }

  inline float GetValue(const healthcare::Person& state) const {
    return values_[state.shocks][state.fitness][CashDiff(state.cash)];
  }

  inline healthcare::DecisionResults GetResult(
      const healthcare::Person& state) const {
    return results_[state.shocks][state.fitness][CashDiff(state.cash)];
  }
  inline unsigned int CashDiff(int cash) const {
    return static_cast<unsigned int>(cash - config_->min_savings);
  }
  bool IsValidState(const healthcare::Person& state) const;
  friend std::ostream& operator<<(std::ostream& out, const Storage& s);

 private:
  unsigned int GetIndex(const healthcare::Person& state) const;

  std::vector<std::vector<std::vector<healthcare::DecisionResults>>> results_;
  std::vector<std::vector<std::vector<float>>> values_;

  std::shared_ptr<const healthcare::Configuration> config_;
  const unsigned int n_elements_;
};

}  // namespace dp
#endif  // DP_STORAGE_H_
