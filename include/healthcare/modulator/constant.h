#ifndef _HEALTHCARE_MODULATOR_CONSTANT_H_
#define _HEALTHCARE_MODULATOR_CONSTANT_H_

#include "healthcare/modulator.h"

#include <boost/math/constants/constants.hpp>
#include <cmath>

namespace healthcare {
namespace modulator {

class Constant : public Modulator {
 public:
  Constant(float modulation) : modulation_(modulation) {}
  float GetModulation(int shocks, int fitness) const override { return modulation_; }
  static Constant NoModulation() {return Constant(0);}
  float modulation_;
};

}  // namespace modulator
}  // namespace healthcare

#endif  // _HEALTHCARE_MODULATOR_CONSTANT_H_
