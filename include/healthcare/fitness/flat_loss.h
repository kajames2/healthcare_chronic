#ifndef HEALTHCARE_FITNESS_FLAT_LOSS_H_
#define HEALTHCARE_FITNESS_FLAT_LOSS_H_

#include <algorithm>

#include "healthcare/fitness.h"

namespace healthcare {
namespace fitness {

class FlatLoss : public Fitness {
 public:
  explicit FlatLoss(int degen) : degen_(degen) {}
  double GetDecimalFitness(double fitness, int fitness_investment) const override {
    return std::max(0.0, fitness - degen_);
  }
  int GetFitnessCost(int fitness, int end_fitness) const override {
    return end_fitness == GetFitness(fitness, 0) ? 0 : 10000;
  }

 private:
  int degen_;
};

}  // namespace fitness
}  // namespace healthcare
#endif  // HEALTHCARE_FITNESS_FLAT_LOSS_H_
