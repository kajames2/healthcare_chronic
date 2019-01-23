#ifndef _HEALTHCARE_FITNESS_COMPOSITE_H_
#define _HEALTHCARE_FITNESS_COMPOSITE_H_

#include "healthcare/fitness.h"

#include <memory>
#include <vector>

namespace healthcare {
namespace fitness {

class Composite : public Fitness {
 public:
  Composite(int max_fitness, int max_budget, std::vector<std::shared_ptr<const Fitness>>);
  int GetFitness(int fitness, int fitness_investment) const override;
  int GetFitnessCost(int fitness, int end_fitness) const override;

 private:
  int max_fitness_;
  std::vector<std::shared_ptr<const Fitness>> fits_;
  std::vector<std::vector<int>> costs_;
};

}  // namespace fitness
}  // namespace healthcare
#endif  // _HEALTHCARE_FITNESS_COMPOSITE_H_
