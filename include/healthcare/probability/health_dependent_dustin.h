#ifndef HEALTHCARE_PROBABILITY_HEALTH_DEPENDENT_DUSTIN_H_
#define HEALTHCARE_PROBABILITY_HEALTH_DEPENDENT_DUSTIN_H_

#include <algorithm>
#include <cmath>

#include "healthcare/probability.h"

namespace healthcare {
namespace probability {

class HealthDependentDustin : public Probability {
 public:
  HealthDependentDustin(float alpha, float beta, float eta, 
		  float fitness_r, float mu, float lambda, int max_age, int max_shocks)
      : alpha_(alpha),
	beta_(beta),
        eta_(eta),
        max_age_(max_age),
        max_shocks_(max_shocks),
	fitness_r_(fitness_r),
	mu_(mu),
	lambda_(lambda) {
  }

  float GetProbability(int age, int shocks, int fitness) const override {
    double health = std::max(
        0.0, mu_ - lambda_ * (max_shocks_ + shocks) /
                     (2.0 * max_shocks_ + fitness_r_ * fitness));
    
    return std::clamp((1 - eta_ * health) * alpha_ * std::exp(beta_ * age), 0.0d, 1.0d);
  }

 private:
  float alpha_;
  float beta_;
  float eta_;
  float fitness_r_;
  float mu_;
  float lambda_;
  int max_age_;
  int max_shocks_;
};

}  // namespace probability
}  // namespace healthcare

#endif  // HEALTHCARE_PROBABILITY_HEALTH_DEPENDENT_DUSTIN_H_
