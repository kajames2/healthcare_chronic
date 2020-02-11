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
  Modifier(modifier::Param param, modifier::Func func)
      : param_(param), func_(func) {}
  virtual float Modify(float val, int age, int shocks, int fitness) const {
    int x;
    switch (param_) {
      case modifier::Param::AGE:
        x = age;
        break;
      case modifier::Param::SHOCKS:
        x = shocks;
        break;
      case modifier::Param::FITNESS:
        x = fitness;
        break;
    }
    switch (func_) {
      case modifier::Func::ADD:
        return val + this->GetModification(x);
      case modifier::Func::MULTIPLY:
        return val * this->GetModification(x);
    }
    assert(false);
  }

  virtual float GetModification(int param) const = 0;
  virtual ~Modifier() {}

 private:
  modifier::Param param_;
  modifier::Func func_;
};

}  // namespace healthcare

#endif  // HEALTHCARE_MODIFIER_H_
