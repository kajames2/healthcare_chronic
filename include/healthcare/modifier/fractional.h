#ifndef HEALTHCARE_MODIFIER_FRACTIONAL_H_
#define HEALTHCARE_MODIFIER_FRACTIONAL_H_

#include "healthcare/modifier/single_type.h"

namespace healthcare {
namespace modifier {

class Fractional : public SingleType {
 public:
  Fractional(Param param, Func func, float max_modification, float j)
      : SingleType(param, func), max_modification_(max_modification), j_(j) {}
  float GetModification(int param) const override {
    return (1 - max_modification_) +
           max_modification_ * (1 - param / (param + j_));
  }

  float j_;
  float max_modification_;
};

}  // namespace modifier
}  // namespace healthcare

#endif  // HEALTHCARE_MODIFIER_FRACTIONAL_H_
