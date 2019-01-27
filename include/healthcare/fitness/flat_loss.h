#ifndef _HEALTHCARE_FITNESS_FLAT_LOSS_H_
#define _HEALTHCARE_FITNESS_FLAT_LOSS_H_

#include "healthcare/fitness.h"

#include <algorithm>

namespace healthcare {
namespace fitness {

class FlatLoss : public Fitness {
 public:
  FlatLoss(int degen) : degen_(degen) {}
  int GetFitness(int fitness, int fitness_investment) const override {
    return std::max(0, fitness - degen_);
  }
  int GetFitnessCost(int fitness, int end_fitness) const override {
    return end_fitness == GetFitness(fitness, 0) ? 0 : 10000;
  }

 private:
  int degen_;
};

}  // namespace fitness
}  // namespace healthcare
#endif  // _HEALTHCARE_FITNESS_FLAT_LOSS_H_
