#ifndef HEALTHCARE_SHIFTER_H_
#define HEALTHCARE_SHIFTER_H_

namespace healthcare {

class Shifter {
 public:
  virtual float GetShift(int shocks, int fitness) const = 0;
  virtual ~Shifter() {}
};

}  // namespace healthcare

#endif  // HEALTHCARE_SHIFTER_H_
