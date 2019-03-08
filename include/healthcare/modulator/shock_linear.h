#ifndef HEALTHCARE_MODULATOR_SHOCK_LINEAR_H_
#define HEALTHCARE_MODULATOR_SHOCK_LINEAR_H_

#include "healthcare/modulator.h"

namespace healthcare {
namespace modulator {

class ShockLinear : public Modulator {
 public:
  ShockLinear(float max_modulation, int max_shocks)
      : max_modulation_(max_modulation), max_shocks_(max_shocks) {}
  float GetModulation(int shocks, int fitness) const override {
    return 1 - (max_modulation_ * shocks) / max_shocks_;
  }

  int max_shocks_;
  float max_modulation_;
};

}  // namespace modulator
}  // namespace healthcare

#endif  // HEALTHCARE_MODULATOR_SHOCK_LINEAR_H_
