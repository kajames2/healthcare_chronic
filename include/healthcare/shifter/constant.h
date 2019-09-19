#ifndef HEALTHCARE_SHIFTER_CONSTANT_H_
#define HEALTHCARE_SHIFTER_CONSTANT_H_

#include "healthcare/shifter.h"

namespace healthcare {
namespace shifter {

class Constant : public Shifter {
 public:
  explicit Constant(float shift, int max_shocks) : shift_(shift), max_shocks_(max_shocks) {}
  float GetShift(int shocks, int fitness) const override { return shocks < max_shocks_ ? shift_ : 0; }
  static Constant NoShift() { return Constant(0, 0); }
  float shift_;
  int max_shocks_;
};

}  // namespace shifter
}  // namespace healthcare

#endif  // HEALTHCARE_SHIFTER_CONSTANT_H_
