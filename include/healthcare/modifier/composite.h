#ifndef HEALTHCARE_MODIFIER_COMPOSITE_H_
#define HEALTHCARE_MODIFIER_COMPOSITE_H_

#include <memory>
#include <vector>

#include "healthcare/modifier.h"

namespace healthcare {
namespace modifier {

class Composite : public Modifier {
 public:
  Composite(std::vector<std::shared_ptr<const Modifier>> mods)
      : Modifier(Func::ADD), mods_(mods) {}
  float Modify(float val, int age, int shocks, int fitness) const override {
    for (const auto& mod : mods_) {
      val = mod->Modify(val, age, shocks, fitness);
    }
    return val;
  }
  float Modify(int age, int shocks, int fitness) const override { return 0; }

 private:
  std::vector<std::shared_ptr<const Modifier>> mods_;
};

}  // namespace modifier
}  // namespace healthcare
#endif  // HEALTHCARE_MODIFIER_COMPOSITE_H_
