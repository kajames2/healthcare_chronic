#include "healthcare/fitness/quadratic_cost.h"

#include <cmath>

namespace healthcare {
namespace fitness {

QuadraticCost::QuadraticCost(float coeff) : coeff_(coeff) {}

int QuadraticCost::GetFitness(int fitness, int fitness_investment) const {
  return fitness +
         static_cast<int>(coeff_ * fitness_investment * fitness_investment);
}

int QuadraticCost::GetFitnessCost(int fitness, int end_fitness) const {
  if (end_fitness < fitness) {
    return 100000;
  }

  return static_cast<int>(std::sqrt((end_fitness - fitness) / coeff_));
}

}  // namespace fitness
}  // namespace healthcare
