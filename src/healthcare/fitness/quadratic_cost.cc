#include "healthcare/fitness/quadratic_cost.h"

#include <cmath>

namespace healthcare {
namespace fitness {

QuadraticCost::QuadraticCost(float coeff) : coeff_(coeff) {}

double QuadraticCost::GetDecimalFitness(double fitness,
                                        int fitness_investment) const {
  return fitness + std::sqrt(fitness_investment / coeff_);
}

int QuadraticCost::GetFitnessCost(int fitness, int end_fitness) const {
  if (end_fitness < fitness) {
    return 100000;
  }

  return static_cast<int>(
      std::ceil(coeff_ * (end_fitness - fitness) * (end_fitness - fitness)));
}

}  // namespace fitness
}  // namespace healthcare
