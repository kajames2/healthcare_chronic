#ifndef _HEALTHCARE_PROBABILITY_GOMPERTZ_SHOCKS_
#define _HEALTHCARE_PROBABILITY_GOMPERTZ_SHOCKS_

#include <cmath>

#include "healthcare/probability.h"

namespace healthcare {
namespace probability {

class GompertzShocks : public Probability {
 public:
  GompertzShocks(float age_coeff, float age_rate, float shock_coeff,
                 float shock_rate)
      : age_coeff_(age_coeff),
        age_rate_(age_rate),
        shock_coeff_(shock_coeff),
        shock_rate_(shock_rate) {}
  float GetProbability(int age, int shocks, int fitness) const override {
    return (age_coeff_ * std::exp(age_rate_ * age) +
            shock_coeff_ * std::exp(shock_rate_ * shocks));
  }

 private:
  float age_coeff_;
  float age_rate_;
  float shock_coeff_;
  float shock_rate_;
  float max_fitness_mod_;
  int max_fitness_;
};

}  // namespace probability
}  // namespace healthcare

#endif  // _HEALTHCARE_PROBABILITY_GOMPERTZ_SHOCKS_
