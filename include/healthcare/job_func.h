#ifndef HEALTHCARE_JOB_FUNC_H_
#define HEALTHCARE_JOB_FUNC_H_

#include <string>
#include <unordered_map>
#include "exprtk.hpp"

namespace healthcare {

class JobFunc {
 public:
  JobFunc(const std::string& func_str,
          std::unordered_map<std::string, double> job_consts,
          unsigned int max_age, unsigned int max_shocks,
          unsigned int max_fitness);

  int operator()(unsigned int age, unsigned int shocks,
                 unsigned int fitness) const;

 private:
  mutable double age_ = 1;
  mutable double shocks_ = 0;
  mutable double fitness_ = 0;
  double max_age_;
  double max_shocks_;
  double max_fitness_;
  std::unordered_map<std::string, double> job_consts_;
  std::string expression_str_;
  exprtk::parser<double> parser_;
  exprtk::expression<double> expression_;
};

}  // namespace healthcare

#endif  // HEALTHCARE_JOB_FUNC_H_
