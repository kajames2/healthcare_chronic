#ifndef HEALTHCARE_INSURANCE_ACTUARIAL_H_
#define HEALTHCARE_INSURANCE_ACTUARIAL_H_

#include <cmath>
#include <memory>

#include "healthcare/insurance.h"
#include "healthcare/probability.h"

namespace healthcare {
namespace insurance {

class Actuarial : public Insurance {
 public:
  Actuarial(float scale, float admin_cost, int shock_income_size,
            std::shared_ptr<const Probability> prob)
      : scale_(scale), admin_cost_(admin_cost), shock_income_size_(shock_income_size), prob_(prob) {}
  float GetPrice(int age, int shocks, int fitness) const override {
    auto prob = prob_->GetProbability(age, shocks, fitness);
    return std::round(scale_ * prob * shock_income_size_ + admin_cost_);
  }

 private:
  float scale_;
  float admin_cost_;
  int shock_income_size_;
  std::shared_ptr<const Probability> prob_;
};

}  // namespace insurance
}  // namespace healthcare
#endif  // HEALTHCARE_INSURANCE_ACTUARIAL_H_
