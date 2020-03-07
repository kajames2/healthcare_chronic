#ifndef HEALTHCARE_MODIFIER_H_
#define HEALTHCARE_MODIFIER_H_

#include <cassert>

namespace healthcare {

namespace modifier {
enum class Param { AGE = 0, SHOCKS, FITNESS };
enum class Func { ADD = 0, MULTIPLY };
}  // namespace modifier

class Modifier {
 public:
  Modifier(modifier::Func func) : func_(func) {}
  virtual float Modify(float val, int age, int shocks, int fitness) const {
    switch (func_) {
      case modifier::Func::ADD:
        return val + this->Modify(age, shocks, fitness);
      case modifier::Func::MULTIPLY:
        return val * this->Modify(age, shocks, fitness);
    }
    assert(false);
  }

  virtual float Modify(int age, int shocks, int fitness) const = 0;
  virtual ~Modifier() {}

 private:
  modifier::Func func_;
};

}  // namespace healthcare

#endif  // HEALTHCARE_MODIFIER_H_
