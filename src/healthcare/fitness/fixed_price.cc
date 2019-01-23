#include "healthcare/fitness/fixed_price.h"

#include <algorithm>

namespace healthcare {
namespace fitness {

FixedPrice::FixedPrice(int price)
    : price_(price) {}

int FixedPrice::GetFitness(int fitness, int fitness_investment) const {
  return fitness + (fitness_investment / price_);
}

int FixedPrice::GetFitnessCost(int fitness, int end_fitness) const {
  if (end_fitness < fitness) {
    return 100000;
  }

  return (end_fitness - fitness) * price_;
}

}  // namespace fitness
}  // namespace healthcare
