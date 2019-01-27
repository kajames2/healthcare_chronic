#ifndef _HEALTHCARE_FITNESS_FIXED_PRICE_H_
#define _HEALTHCARE_FITNESS_FIXED_PRICE_H_

#include "healthcare/fitness.h"

namespace healthcare {
namespace fitness {

class FixedPrice : public Fitness {
 public:
  FixedPrice(int price);
  int GetFitness(int fitness, int fitness_investment) const override;
  int GetFitnessCost(int fitness, int end_fitness) const override;

 private:
  int price_;
};

}  // namespace fitness
}  // namespace healthcare
#endif  // _HEALTHCARE_FITNESS_FIXED_PRICE_H_
