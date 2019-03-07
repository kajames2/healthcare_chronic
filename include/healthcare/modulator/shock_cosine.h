#ifndef _HEALTHCARE_MODULATOR_SHOCK_COSINE_H_
#define _HEALTHCARE_MODULATOR_SHOCK_COSINE_H_

#include "healthcare/modulator.h"

#include <boost/math/constants/constants.hpp>
#include <cmath>

namespace healthcare {
namespace modulator {

class ShockCosine : public Modulator {
 public:
  ShockCosine(float max_modulation, int max_shocks)
      : max_modulation_(max_modulation), max_shocks_(max_shocks) {}
  float GetModulation(int shocks, int fitness) const override {
    static const double pi = boost::math::constants::pi<double>();
    return max_modulation_ *
           std::sqrt(std::cos(pi / (2 * max_shocks_) * shocks));
  }

  int max_shocks_;
  float max_modulation_;
};

}  // namespace modulator
}  // namespace healthcare

#endif  // _HEALTHCARE_MODULATOR_SHOCK_COSINE_H_
