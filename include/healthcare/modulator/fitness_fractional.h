#ifndef _HEALTHCARE_MODULATOR_FITNESS_FRACTIONAL_H_
#define _HEALTHCARE_MODULATOR_FITNESS_FRACTIONAL_H_

#include "healthcare/modulator.h"

namespace healthcare {
namespace modulator {

class FitnessFractional : public Modulator {
 public:
  FitnessFractional(float max_modulation, float j)
      : max_modulation_(max_modulation), j_(j) {}
  float GetModulation(int shocks, int fitness) const override {
    return 1 - (max_modulation_ *  fitness / (fitness + j_));
  }

  float j_;
  float max_modulation_;
};

}  // namespace modulator
}  // namespace healthcare

#endif  // _HEALTHCARE_MODULATOR_FITNESS_FRACTIONAL_H_
