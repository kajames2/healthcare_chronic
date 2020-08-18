#ifndef HEALTHCARE_INSURANCE_ACTUARIAL_H_
#define HEALTHCARE_INSURANCE_ACTUARIAL_H_

#include <cmath>
#include <functional>
#include <memory>

#include "healthcare/insurance.h"

namespace healthcare {
namespace insurance {

class Actuarial : public Insurance {
 public:
  Actuarial(float scale, float admin_cost, int shock_income_size,
            std::function<float(int, int, int)> prob)
      : scale_(scale),
        admin_cost_(admin_cost),
        shock_income_size_(shock_income_size),
        prob_(prob) {}
  float GetPrice(int age, int shocks, int fitness) const override {
    auto prob = prob_(age, shocks, fitness);
    return std::ceil(scale_ * prob * shock_income_size_ + admin_cost_);
  }

 private:
  float scale_;
  float admin_cost_;
  int shock_income_size_;
  std::function<float(int, int, int)> prob_;
};

}  // namespace insurance
}  // namespace healthcare
#endif  // HEALTHCARE_INSURANCE_ACTUARIAL_H_
