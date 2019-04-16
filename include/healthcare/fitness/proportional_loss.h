#ifndef HEALTHCARE_FITNESS_PROPORTIONAL_LOSS_H_
#define HEALTHCARE_FITNESS_PROPORTIONAL_LOSS_H_

#include <algorithm>
#include <cmath>

#include "healthcare/fitness.h"

namespace healthcare {
namespace fitness {

class ProportionalLoss : public Fitness {
 public:
  explicit ProportionalLoss(double rate) : rate_(rate) {}
  double GetDecimalFitness(double fitness, int fitness_investment) const override {
    return (1 - rate_) * fitness + 0.00001;
  }
  int GetFitnessCost(int fitness, int end_fitness) const override {
    return end_fitness == GetFitness(fitness, 0) ? 0 : 10000;
  }

 private:
  double rate_;
};

}  // namespace fitness
}  // namespace healthcare
#endif  // HEALTHCARE_FITNESS_PROPORTIONAL_LOSS_H_
