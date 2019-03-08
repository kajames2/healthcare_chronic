#ifndef HEALTHCARE_JOB_DEFINED_H_
#define HEALTHCARE_JOB_DEFINED_H_

#include <vector>

#include "healthcare/job.h"

namespace healthcare {
namespace job {

class Defined : public Job {
 public:
  explicit Defined(std::vector<int> earnings) : earnings_(earnings) {}
  int GetEarnings(int age) const override {
    return age <= earnings_.size() ? earnings_[age - 1] : 0;
  };

 private:
  std::vector<int> earnings_;
};

}  // namespace job
}  // namespace healthcare
#endif  // HEALTHCARE_JOB_DEFINED_H_
