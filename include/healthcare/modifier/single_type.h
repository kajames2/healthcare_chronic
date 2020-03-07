#ifndef HEALTHCARE_MODIFIER_SINGLE_TYPE_H_
#define HEALTHCARE_MODIFIER_SINGLE_TYPE_H_

namespace healthcare {
namespace modifier {

class SingleType : public Modifier {
 public:
  SingleType(modifier::Param param, modifier::Func func)
      : Modifier(func), param_(param) {}
  virtual float Modify(int age, int shocks, int fitness) const override {
    int x;
    switch (param_) {
      case Param::AGE:
        x = age;
        break;
      case Param::SHOCKS:
        x = shocks;
        break;
      case Param::FITNESS:
        x = fitness;
        break;
      default:
        assert(false);
    }
    GetModification(x);
  }

  virtual float GetModification(int param) const = 0;
  virtual ~SingleType() {}

 private:
  Param param_;
};

}  // namespace modifier
}  // namespace healthcare

#endif  // HEALTHCARE_MODIFIER_SINGLE_TYPE_H_
