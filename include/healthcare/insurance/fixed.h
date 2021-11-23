#ifndef HEALTHCARE_INSURANCE_FIXED_H_
#define HEALTHCARE_INSURANCE_FIXED_H_

#include "healthcare/insurance.h"

namespace healthcare {
namespace insurance {

class Fixed : public Insurance {
 public:
  explicit Fixed(unsigned int cost) : cost_(cost) {}
  float GetPrice(unsigned int age, unsigned int shocks,
                 unsigned int fitness) const override {
    return static_cast<float>(cost_);
  }

 private:
  unsigned int cost_;
};

}  // namespace insurance
}  // namespace healthcare
#endif  // HEALTHCARE_INSURANCE_FIXED_H_
