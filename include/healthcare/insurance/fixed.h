#ifndef _HEALTHCARE_INSURANCE_FIXED_H_
#define _HEALTHCARE_INSURANCE_FIXED_H_

#include "healthcare/insurance.h"

namespace healthcare {
namespace insurance {

class Fixed : public Insurance {
 public:
  Fixed(int cost) : cost_(cost) {}
  float GetPrice(int age, int shocks, int fitness) const override { return cost_; }

 private:
  int cost_;
};

}  // namespace insurance
}  // namespace healthcare
#endif  // _HEALTHCARE_INSURANCE_FIXED_H_
