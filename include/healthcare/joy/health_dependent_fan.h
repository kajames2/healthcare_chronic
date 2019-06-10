#ifndef HEALTHCARE_JOY_HEALTH_DEPENDENT_FAN_H_
#define HEALTHCARE_JOY_HEALTH_DEPENDENT_FAN_H_

#include <algorithm>
#include <cmath>

#include "healthcare/joy.h"

namespace healthcare {
namespace joy {

class HealthDependentFan : public Joy {
 public:
  explicit HealthDependentFan(double gamma_health, double gamma_consumption,
                              float p, float k, float c,
			      int max_shocks, int max_fitness)
      : gamma_health_(gamma_health),
        gamma_consumption_(gamma_consumption),
        max_shocks_(max_shocks),
	max_fitness_(max_fitness),
	p_(p),
	k_(k),
	c_(c) {}

    double GetJoy(int age, int shocks, int fitness,
                  int investment) const override {
    double min_health = p_ * (max_shocks_ - shocks)/max_shocks_ - k_;
    double health = std::max(
        0.0,  min_health + fitness/max_fitness_ * (1 - shocks * p_/(c_*max_shocks_) - min_health));

    return health * (investment + gamma_health_) /
           (health * (investment + gamma_health_) + gamma_consumption_);
  }

 private:
  double gamma_health_;
  double gamma_consumption_;
  float p_;
  float k_;
  float c_;
  double max_shocks_;
  double max_fitness_;
};

}  // namespace joy
}  // namespace healthcare
#endif  // HEALTHCARE_JOY_HEALTH_DEPENDENT_FAN_H_
