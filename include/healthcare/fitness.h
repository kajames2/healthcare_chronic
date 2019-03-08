#ifndef HEALTHCARE_FITNESS_H_
#define HEALTHCARE_FITNESS_H_

namespace healthcare {

class Fitness {
 public:
  virtual ~Fitness() {}

  virtual int GetFitness(int fitness, int fitness_investment) const = 0;
  virtual int GetFitnessCost(int fitness, int end_fitness) const = 0;
};

}  // namespace healthcare
#endif  // HEALTHCARE_FITNESS_H_
