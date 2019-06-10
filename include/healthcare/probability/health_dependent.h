#ifndef HEALTHCARE_PROBABILITY_HEALTH_DEPENDENT_H_
#define HEALTHCARE_PROBABILITY_HEALTH_DEPENDENT_H_

#include <algorithm>
#include <cmath>

#include "healthcare/probability.h"

namespace healthcare {
namespace probability {

class HealthDependent : public Probability {
 public:
  HealthDependent(float alpha, float beta, float eta, 
		  float fitness_r, int max_age, int max_shocks)
      : alpha_(alpha),
	beta_(beta),
        eta_(eta),
        max_age_(max_age),
        max_shocks_(max_shocks),
	fitness_r_(fitness_r) {
  }

  float GetProbability(int age, int shocks, int fitness) const override {
    float health = std::max(
        0.0, 1 - std::pow(max_shocks_ + shocks, 2) /
                     (2 * max_shocks_ * (max_shocks_ + shocks) + fitness_r_ * fitness));
    
    return std::clamp((1 - eta_ * health) * alpha_ * std::exp(beta_ * age), 0.0f, 1.0f);
  }

 private:
  float alpha_;
  float beta_;
  float fitness_r_;
  float eta_;
  int max_age_;
  int max_shocks_;
};

}  // namespace probability
}  // namespace healthcare

#endif  // HEALTHCARE_PROBABILITY_HEALTH_DEPENDENT_H_
