#ifndef HEALTHCARE_INSURANCE_H_
#define HEALTHCARE_INSURANCE_H_

namespace healthcare {

class Insurance {
 public:
  virtual float GetPrice(int age, int shocks, int fitness) const = 0;
  virtual ~Insurance() {}
};

}  // namespace healthcare
#endif  // HEALTHCARE_INSURANCE_H_
