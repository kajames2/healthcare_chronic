#ifndef HEALTHCARE_JOY_MOD_DECORATOR_H_
#define HEALTHCARE_JOY_MOD_DECORATOR_H_

#include <memory>

#include "healthcare/joy.h"
#include "healthcare/modulator.h"

namespace healthcare {
namespace joy {

class ModDecorator : public Joy {
 public:
  ModDecorator(std::shared_ptr<const Joy> prob,
               std::shared_ptr<const Modulator> mod)
      : prob_(prob), mod_(mod) {}
  double GetJoy(int age, int shocks, int fitness,
                int investment) const override {
    return prob_->GetJoy(age, shocks, fitness, investment) *
           mod_->GetModulation(shocks, fitness);
  };

 private:
  std::shared_ptr<const Joy> prob_;
  std::shared_ptr<const Modulator> mod_;
};

}  // namespace joy
}  // namespace healthcare

#endif  // HEALTHCARE_JOY_MOD_DECORATOR_H_
