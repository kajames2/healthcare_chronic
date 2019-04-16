#ifndef HEALTHCARE_FITNESS_H_
#define HEALTHCARE_FITNESS_H_

#include <cmath>

namespace healthcare {

class Fitness {
 public:
  virtual ~Fitness() {}

  virtual int GetFitness(int fitness, int fitness_investment) const {
    return static_cast<int>(GetDecimalFitness(fitness, fitness_investment));
  };
  virtual int GetFitnessCost(int fitness, int end_fitness) const = 0;
  virtual double GetDecimalFitness(double fitness,
                                   int fitness_investment) const = 0;

 protected:
};

}  // namespace healthcare
#endif  // HEALTHCARE_FITNESS_H_
