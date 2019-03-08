#ifndef HEALTHCARE_JOY_H_
#define HEALTHCARE_JOY_H_

namespace healthcare {

class Joy {
 public:
  virtual double GetJoy(int shocks, int life_investment) const = 0;
  virtual ~Joy() {}
};

}  // namespace healthcare
#endif  // HEALTHCARE_JOY_H_
