#ifndef HEALTHCARE_PROBABILITY_HEALTH_DEPENDENT_STEVE_H_
#define HEALTHCARE_PROBABILITY_HEALTH_DEPENDENT_STEVE_H_

#include <algorithm>
#include <cmath>

#include "healthcare/probability.h"

namespace healthcare {
namespace probability {

class HealthDependentSteve : public Probability {
 public:
  HealthDependentSteve(float alpha, float beta, float eta, 
		  float fitness_r, float lambda, float mu, int max_age, int max_shocks)
      : alpha_(alpha),
	beta_(beta),
        eta_(eta),
        max_age_(max_age),
        max_shocks_(max_shocks),
	fitness_r_(fitness_r),
	lambda_(lambda),
	mu_(mu) {
  }

  float GetProbability(int age, int shocks, int fitness) const override {
    double health = std::max(
        0.0, mu_ - (max_shocks_ + shocks) /
                     (2.0 * max_shocks_ + fitness_r_ * (fitness - lambda_)));
    
    return std::clamp((1 - eta_ * health) * alpha_ * std::exp(beta_ * age), 0.0d, 1.0d);
  }

 private:
  float alpha_;
  float beta_;
  float eta_;
  float fitness_r_;
  float lambda_;
  float mu_;
  int max_age_;
  int max_shocks_;
};

}  // namespace probability
}  // namespace healthcare

#endif  // HEALTHCARE_PROBABILITY_HEALTH_DEPENDENT_STEVE_H_
