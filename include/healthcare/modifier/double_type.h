#ifndef HEALTHCARE_MODIFIER_DOUBLE_TYPE_H_
#define HEALTHCARE_MODIFIER_DOUBLE_TYPE_H_

#include "healthcare/modifier.h"

#include <array>

namespace healthcare {
namespace modifier {

class DoubleType : public Modifier {
 public:
  DoubleType(Param param1, Param param2, modifier::Func func)
      : Modifier(func), param1_(param), param2_(param) {}
  virtual float Modify(int age, int shocks, int fitness) const override {
    std::array<int, 3> arr = {age, shocks, fitness};
    int x = arr[param1_];
    int y = arr[param2_];
    GetModification(x, y);
  }

  virtual float GetModification(int param1, int param2) const = 0;
  virtual ~Modifier() {}

 private:
  Param param1_;
  Param param2_;
};

}  // namespace modifier
}  // namespace healthcare

#endif  // HEALTHCARE_MODIFIER_DOUBLE_TYPE_H_
