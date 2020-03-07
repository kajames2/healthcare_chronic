#ifndef HEALTHCARE_MODIFIER_CONSTANT_H_
#define HEALTHCARE_MODIFIER_CONSTANT_H_


#include "healthcare/modifier.h"

namespace healthcare {
namespace modifier {

class Constant : public Modifier {
 public:
  explicit Constant(Func func, float modification)
      : Modifier(func), modification_(modification) {}
  float Modify(int, int, int) const override { return modification_; }

  static Constant NoModification() { return Constant(Func::ADD, 0); }
  float modification_;
};

}  // namespace modifier
}  // namespace healthcare

#endif  // HEALTHCARE_MODIFIER_CONSTANT_H_
