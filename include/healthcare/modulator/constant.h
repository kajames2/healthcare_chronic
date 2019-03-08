#ifndef HEALTHCARE_MODULATOR_CONSTANT_H_
#define HEALTHCARE_MODULATOR_CONSTANT_H_

#include <cmath>

#include <boost/math/constants/constants.hpp>
#include "healthcare/modulator.h"

namespace healthcare {
namespace modulator {

class Constant : public Modulator {
 public:
  explicit Constant(float modulation) : modulation_(modulation) {}
  float GetModulation(int shocks, int fitness) const override {
    return modulation_;
  }
  static Constant NoModulation() { return Constant(0); }
  float modulation_;
};

}  // namespace modulator
}  // namespace healthcare

#endif  // HEALTHCARE_MODULATOR_CONSTANT_H_
