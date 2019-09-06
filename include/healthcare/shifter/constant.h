#ifndef HEALTHCARE_SHIFTER_CONSTANT_H_
#define HEALTHCARE_SHIFTER_CONSTANT_H_

#include "healthcare/shifter.h"

namespace healthcare {
namespace shifter {

class Constant : public Shifter {
 public:
  explicit Constant(float shift) : shift_(shift) {}
  float GetShift(int shocks, int fitness) const override { return shift_; }
  static Constant NoShift() { return Constant(0); }
  float shift_;
};

}  // namespace shifter
}  // namespace healthcare

#endif  // HEALTHCARE_SHIFTER_CONSTANT_H_
