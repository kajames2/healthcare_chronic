#ifndef HEALTHCARE_JOB_H_
#define HEALTHCARE_JOB_H_

namespace healthcare {

class Job {
 public:
  virtual int GetEarnings(int age) const = 0;
  virtual ~Job() {}
};

}  // namespace healthcare
#endif  // HEALTHCARE_JOB_H_
