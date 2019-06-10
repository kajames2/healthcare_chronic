#ifndef HEALTHCARE_PROBABILITY_HEALTH_DEPENDENT_FAN_H_
#define HEALTHCARE_PROBABILITY_HEALTH_DEPENDENT_FAN_H_

#include <algorithm>
#include <cmath>

#include "healthcare/probability.h"

namespace healthcare {
namespace probability {

class HealthDependentFan : public Probability {
 public:
  HealthDependentFan(float alpha, float beta, float eta, 
		     float p, float k, float c,
		     int max_age, int max_shocks, int max_fitness)
      : alpha_(alpha),
	beta_(beta),
        eta_(eta),
        max_age_(max_age),
        max_shocks_(max_shocks),
	max_fitness_(max_fitness),
	p_(p),
	k_(k),
        c_(c) {
  }

  float GetProbability(int age, int shocks, int fitness) const override {
    double min_health = p_ * (max_shocks_ - shocks)/max_shocks_ - k_;
    double health = std::max(
        0.0,  min_health + fitness/max_fitness_ * (1 - shocks * p_/(c_*max_shocks_) - min_health));
    
    return std::clamp((1 - eta_ * health) * alpha_ * std::exp(beta_ * age), 0.0d, 1.0d);
  }

 private:
  float alpha_;
  float beta_;
  float eta_;
  float p_;
  float k_;
  float c_;
  double max_age_;
  double max_shocks_;
  double max_fitness_;
};

}  // namespace probability
}  // namespace healthcare

#endif  // HEALTHCARE_PROBABILITY_HEALTH_DEPENDENT_FAN_H_
