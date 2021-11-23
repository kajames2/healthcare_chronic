#ifndef HEALTHCARE_FITNESS_FUNC_H_
#define HEALTHCARE_FITNESS_FUNC_H_

#include <string>
#include <unordered_map>
#include "exprtk.hpp"

namespace healthcare {

class FitnessFunc {
 public:
  FitnessFunc(const std::string& func_str,
              std::unordered_map<std::string, double> fitness_consts,
              unsigned int max_age, unsigned int max_shocks,
              unsigned int max_fitness);

  unsigned int operator()(unsigned int age, unsigned int shocks,
                          unsigned int fitness, unsigned int investment) const;

 private:
  mutable double age_ = 1;
  mutable double shocks_ = 0;
  mutable double fitness_ = 0;
  mutable double x_ = 0;
  double max_age_;
  double max_shocks_;
  double max_fitness_;
  std::unordered_map<std::string, double> fitness_consts_;
  std::string expression_str_;
  exprtk::parser<double> parser_;
  exprtk::expression<double> expression_;
};

}  // namespace healthcare

#endif  // HEALTHCARE_FITNESS_FUNC_H_
