#ifndef HEALTHCARE_JOY_MOD_DECORATOR_H_
#define HEALTHCARE_JOY_MOD_DECORATOR_H_

#include <memory>

#include "healthcare/joy.h"
#include "healthcare/modifier.h"

namespace healthcare {
namespace joy {

class ModDecorator : public Joy {
 public:
  ModDecorator(std::shared_ptr<const Joy> prob,
               std::shared_ptr<const Modifier> mod)
      : prob_(prob), mod_(mod) {}
  double GetJoy(int age, int shocks, int fitness,
                int investment) const override {
    float joy = prob_->GetJoy(age, shocks, fitness, investment);
    return mod_->Modify(joy, age, shocks, fitness);
  };

 private:
  std::shared_ptr<const Joy> prob_;
  std::shared_ptr<const Modifier> mod_;
};

}  // namespace joy
}  // namespace healthcare

#endif  // HEALTHCARE_JOY_MOD_DECORATOR_H_
