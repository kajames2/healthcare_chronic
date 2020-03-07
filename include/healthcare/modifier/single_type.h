#ifndef HEALTHCARE_MODIFIER_SINGLE_TYPE_H_
#define HEALTHCARE_MODIFIER_SINGLE_TYPE_H_

namespace healthcare {
namespace modifier {

class SingleType : public Modifier {
 public:
  SingleType(modifier::Param param, modifier::Func func,
             std::shared_ptr<const Modifier> param_mod = nullptr)
      : Modifier(func), param_(param), param_mod_(param_mod) {}
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
    if (param_mod_) {
      x = param_mod_->Modify(x, age, shocks, fitness);
    }
    GetModification(x);
  }

  virtual float GetModification(int param) const = 0;
  virtual ~SingleType() {}

 private:
  Param param_;
  std::shared_ptr<const Modifier> param_mod_;
};

}  // namespace modifier
}  // namespace healthcare

#endif  // HEALTHCARE_MODIFIER_SINGLE_TYPE_H_
