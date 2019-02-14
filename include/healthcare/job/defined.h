#ifndef _HEALTHCARE_JOB_DEFINED_H_
#define _HEALTHCARE_JOB_DEFINED_H_

#include "healthcare/job.h"

#include <vector>

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
#endif  // _HEALTHCARE_JOB_DEFINED_H_
