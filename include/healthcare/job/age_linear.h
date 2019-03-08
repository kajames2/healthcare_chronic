#ifndef HEALTHCARE_JOB_AGE_LINEAR_H_
#define HEALTHCARE_JOB_AGE_LINEAR_H_

#include <cmath>

#include "healthcare/job.h"

namespace healthcare {
namespace job {

class AgeLinear : public Job {
 public:
  explicit AgeLinear(float intercept, float slope) : b_(intercept), m_(slope) {}
  int GetEarnings(int age) const override { return std::round(m_ * age + b_); };

 private:
  float b_;
  float m_;
};

}  // namespace job
}  // namespace healthcare
#endif  // HEALTHCARE_JOB_AGE_LINEAR_H_
