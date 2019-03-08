#ifndef HEALTHCARE_MODULATOR_FITNESS_LINEAR_H_
#define HEALTHCARE_MODULATOR_FITNESS_LINEAR_H_

#include "healthcare/modulator.h"

namespace healthcare {
namespace modulator {

class FitnessLinear : public Modulator  {
 public:
  FitnessLinear(float max_modulation, int max_fitness)
      : max_modulation_(max_modulation), max_fitness_(max_fitness) {}
  float GetModulation(int shocks, int fitness) const override {
    return 1 - (max_modulation_ * fitness) / max_fitness_;
  }

  int max_fitness_;
  float max_modulation_;
};

}  // namespace modulator
}  // namespace healthcare

#endif  // HEALTHCARE_MODULATOR_FITNESS_LINEAR_H_
