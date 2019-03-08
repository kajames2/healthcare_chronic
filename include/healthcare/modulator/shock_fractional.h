#ifndef HEALTHCARE_MODULATOR_SHOCK_FRACTIONAL_H_
#define HEALTHCARE_MODULATOR_SHOCK_FRACTIONAL_H_

#include "healthcare/modulator.h"

namespace healthcare {
namespace modulator {

class ShockFractional : public Modulator {
 public:
  ShockFractional(float max_modulation, float j)
      : max_modulation_(max_modulation), j_(j) {}
  float GetModulation(int shocks, int fitness) const override {
    return 1 - (max_modulation_ *  shocks / (shocks + j_));
  }

  float j_;
  float max_modulation_;
};

}  // namespace modulator
}  // namespace healthcare

#endif  // HEALTHCARE_MODULATOR_SHOCK_FRACTIONAL_H_
