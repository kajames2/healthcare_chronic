#ifndef HEALTHCARE_JOY_HEALTH_DEPENDENT_H_
#define HEALTHCARE_JOY_HEALTH_DEPENDENT_H_

#include <algorithm>
#include <cmath>

#include "healthcare/joy.h"

namespace healthcare {
namespace joy {

class HealthDependent : public Joy {
 public:
  explicit HealthDependent(double gamma_health, double gamma_consumption,
                           int max_shocks)
      : gamma_health_(gamma_health),
        gamma_consumption_(gamma_consumption),
        max_shocks_(max_shocks) {}

  double GetJoy(int age, int shocks, int fitness,
                int investment) const override {
    double health = std::max(
        0.0, 1 - std::pow(max_shocks_ + shocks, 2) /
                     (2 * max_shocks_ * (max_shocks_ + shocks + fitness)));
    return health * (investment + gamma_health_) /
           (health * (investment + gamma_health_) + gamma_consumption_);
  }

 private:
  int max_shocks_;
  double gamma_health_;
  double gamma_consumption_;
};

}  // namespace joy
}  // namespace healthcare
#endif  // HEALTHCARE_JOY_HEALTH_DEPENDENT_H_
