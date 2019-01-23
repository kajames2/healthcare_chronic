#ifndef _HEALTHCARE_INSURANCE_H_
#define _HEALTHCARE_INSURANCE_H_

namespace healthcare {

class Insurance {
 public:
  virtual float GetPrice(int age, int shocks, int fitness) const = 0;
  virtual ~Insurance() {}
};

}  // namespace healthcare
#endif  // _HEALTHCARE_INSURANCE_H_
