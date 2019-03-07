#ifndef HEALTHCARE_FITNESS_QUADRATIC_COST_H_
#define HEALTHCARE_FITNESS_QUADRATIC_COST_H_

#include "healthcare/fitness.h"

namespace healthcare {
namespace fitness {

class QuadraticCost : public Fitness {
 public:
  QuadraticCost(float coeff);
  int GetFitness(int fitness, int fitness_investment) const override;
  int GetFitnessCost(int fitness, int end_fitness) const override;

 private:
  float coeff_;
};

}  // namespace fitness
}  // namespace healthcare
#endif  // HEALTHCARE_FITNESS_FIXED_PRICE_H_
