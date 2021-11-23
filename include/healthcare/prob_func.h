#ifndef HEALTHCARE_PROB_FUNC_H_
#define HEALTHCARE_PROB_FUNC_H_

#include <string>
#include <unordered_map>
#include "exprtk.hpp"

namespace healthcare {

class ProbFunc {
 public:
  ProbFunc(const std::string& func_str,
           std::unordered_map<std::string, double> prob_consts,
           unsigned int max_age, unsigned int max_shocks,
           unsigned int max_fitness);

  float operator()(unsigned int age, unsigned int shocks,
                   unsigned int fitness) const;

 private:
  mutable double age_ = 1;
  mutable double shocks_ = 0;
  mutable double fitness_ = 0;
  double max_age_;
  double max_shocks_;
  double max_fitness_;
  std::unordered_map<std::string, double> prob_consts_;
  std::string expression_str_;
  exprtk::parser<double> parser_;
  exprtk::expression<double> expression_;
};

}  // namespace healthcare

#endif  // HEALTHCARE_PROB_FUNC_H_
