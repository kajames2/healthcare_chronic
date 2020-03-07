#ifndef HEALTHCARE_MODIFIER_PARAM_MODULATOR_H_
#define HEALTHCARE_MODIFIER_PARAM_MODULATOR_H_

#include <memory>

#include "healthcare/modifier.h"
#include "healthcare/modifier/single_type.h"

namespace healthcare {
namespace modifier {

class ParamModulator : public Modifier {
 public:
  ParamModulator(std::shared_ptr<const SingleType> base_mod,
                 std::shared_ptr<const Modifier> param_mod)
      : Modifier(Func::ADD), base_mod_(base_mod), param_mod_(param_mod) {}
  float Modify(float val, int age, int shocks, int fitness) const override {
    for (const auto& mod : mods_) {
      val = mod->Modify(val, age, shocks, fitness);
    }
    return val;
  }
  float Modify(int age, int shocks, int fitness) const override { return 0; }

 private:
  std::shared_ptr<const SingleType> base_mod_;
  std::shared_ptr<const Modifier> param_mod_;
};

}  // namespace modifier
}  // namespace healthcare
#endif  // HEALTHCARE_MODIFIER_PARAM_MODULATOR_H_
