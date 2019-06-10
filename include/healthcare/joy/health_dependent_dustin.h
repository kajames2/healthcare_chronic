#ifndef HEALTHCARE_JOY_HEALTH_DEPENDENT_DUSTIN_H_
#define HEALTHCARE_JOY_HEALTH_DEPENDENT_DUSTIN_H_

#include <algorithm>
#include <cmath>

#include "healthcare/joy.h"

namespace healthcare {
namespace joy {

class HealthDependentDustin : public Joy {
 public:
  explicit HealthDependentDustin(double gamma_health, double gamma_consumption,
                           int max_shocks, float fitness_r, float lambda, float mu)
      : gamma_health_(gamma_health),
        gamma_consumption_(gamma_consumption),
        max_shocks_(max_shocks),
	fitness_r_(fitness_r),
	lambda_(lambda),
	mu_(mu) {}

    double GetJoy(int age, int shocks, int fitness,
                  int investment) const override {
    double health = std::max(
        0.0, mu_ - lambda_ * (max_shocks_ + shocks) /
                     (2.0 * max_shocks_ + fitness_r_ * fitness));

    return health * (investment + gamma_health_) /
           (health * (investment + gamma_health_) + gamma_consumption_);
  }

 private:
  int max_shocks_;
  double gamma_health_;
  double gamma_consumption_;
  float fitness_r_;
  float lambda_;
  float mu_;
};

}  // namespace joy
}  // namespace healthcare
#endif  // HEALTHCARE_JOY_HEALTH_DEPENDENT_DUSTIN_H_
