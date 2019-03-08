#ifndef HEALTHCARE_MODULATOR_H_
#define HEALTHCARE_MODULATOR_H_

namespace healthcare {

class Modulator {
 public:
  virtual float GetModulation(int shocks, int fitness) const = 0;
  virtual ~Modulator() {}
};

}  // namespace healthcare

#endif  // HEALTHCARE_MODULATOR_H_
