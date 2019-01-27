#ifndef _HEALTHCARE_FITNESS_PROPORTIONAL_LOSS_H_
#define _HEALTHCARE_FITNESS_PROPORTIONAL_LOSS_H_

#include "healthcare/fitness.h"

#include <algorithm>
#include <cmath>

namespace healthcare {
namespace fitness {

class ProportionalLoss : public Fitness {
 public:
  ProportionalLoss(double rate) : rate_(rate) {}
  int GetFitness(int fitness, int fitness_investment) const override {
    return std::max(0, static_cast<int>(std::round((1 - rate_) * fitness)));
  }
  int GetFitnessCost(int fitness, int end_fitness) const override {
    return end_fitness == GetFitness(fitness, 0) ? 0 : 10000;
  }

 private:
  double rate_;
};

}  // namespace fitness
}  // namespace healthcare
#endif  // _HEALTHCARE_FITNESS_PROPORTIONAL_LOSS_H_
