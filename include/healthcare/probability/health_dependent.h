#ifndef HEALTHCARE_PROBABILITY_HEALTH_DEPENDENT_H_
#define HEALTHCARE_PROBABILITY_HEALTH_DEPENDENT_H_

#include <algorithm>
#include <cmath>

#include "healthcare/probability.h"

namespace healthcare {
namespace probability {

class HealthDependent : public Probability {
 public:
  HealthDependent(float midlife_prob, float eta, float delta_health,
                  float delta_age, int max_age, int max_shocks)
      : midlife_prob_(midlife_prob),
        eta_(eta),
        delta_health_(delta_health),
        delta_age_(delta_age),
        max_age_(max_age),
        max_shocks_(max_shocks) {
  }

  float GetProbability(int age, int shocks, int fitness) const override {
    float lambda =
        midlife_prob_ -
        delta_health_ * (eta_ - 0.5) *
            std::exp(0.5 *
                     std::log(delta_age_ / (delta_health_ * (eta_ - 1)) + 1));
    float alpha = delta_health_;
    float beta = (1.0 / max_age_) *
                 std::log(delta_age_ / (delta_health_ * (eta_ - 1)) + 1);
    float health = std::max(
        0.0, 1 - std::pow(max_shocks_ + shocks, 2) /
                     (2 * max_shocks_ * (max_shocks_ + shocks + fitness)));
    
    return std::clamp(lambda + (eta_ - health) * alpha * std::exp(beta * age), 0.0f, 1.0f);
  }

 private:
  float midlife_prob_;
  float delta_health_;
  float delta_age_;
  float eta_;
  int max_age_;
  int max_shocks_;
};

}  // namespace probability
}  // namespace healthcare

#endif  // HEALTHCARE_PROBABILITY_GOMPERTZ_MAKEHAM_H_
