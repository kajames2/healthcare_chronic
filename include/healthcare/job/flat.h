#ifndef _HEALTHCARE_JOB_FLAT_H_
#define _HEALTHCARE_JOB_FLAT_H_

#include "healthcare/job.h"

namespace healthcare {
namespace job {

class Flat : public Job {
 public:
  explicit Flat(int rate) : rate_(rate) {}
  int GetEarnings(int age) const override { return rate_; };

 private:
  int rate_;
};

}  // namespace job
}  // namespace healthcare
#endif  // _HEALTHCARE_JOB_FLAT_H_
