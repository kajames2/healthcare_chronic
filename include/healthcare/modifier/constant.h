#ifndef HEALTHCARE_MODIFIER_CONSTANT_H_
#define HEALTHCARE_MODIFIER_CONSTANT_H_

#include <cmath>

#include "healthcare/modifier.h"

namespace healthcare {
namespace modifier {

class Constant : public Modifier {
 public:
  explicit Constant(Func func, float modification)
      : Modifier(Param::AGE, func), modification_(modification) {}
  float GetModification(int) const override { return modification_; }

  static Constant NoModification() {
    return Constant(Func::ADD, 0);
  }
  float modification_;
};

}  // namespace modifier
}  // namespace healthcare

#endif  // HEALTHCARE_MODIFIER_CONSTANT_H_
