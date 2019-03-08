#ifndef HEALTHCARE_MODULATOR_FITNESS_COSINE_H_
#define HEALTHCARE_MODULATOR_FITNESS_COSINE_H_

#include <cmath>

#include <boost/math/constants/constants.hpp>
#include "healthcare/modulator.h"

namespace healthcare {
namespace modulator {

class FitnessCosine : public Modulator {
 public:
  FitnessCosine(float max_modulation, int max_fitness)
      : max_modulation_(max_modulation), max_fitness_(max_fitness) {}
  float GetModulation(int shocks, int fitness) const override {
    static const double pi = boost::math::constants::pi<double>();
    return max_modulation_ *
           std::sqrt(std::cos(pi / (2 * max_fitness_) * fitness));
  }

  int max_fitness_;
  float max_modulation_;
};

}  // namespace modulator
}  // namespace healthcare

#endif  // HEALTHCARE_MODULATOR_FITNESS_COSINE_H_
