#ifndef HEALTHCARE_JOY_SHIFT_DECORATOR_H_
#define HEALTHCARE_JOY_SHIFT_DECORATOR_H_

#include <memory>

#include "healthcare/joy.h"
#include "healthcare/shifter.h"

namespace healthcare {
namespace joy {

class ShiftDecorator : public Joy {
 public:
  ShiftDecorator(std::shared_ptr<const Joy> joy,
               std::shared_ptr<const Shifter> shift)
      : joy_(joy), shift_(shift) {}
  double GetJoy(int age, int shocks, int fitness,
                int investment) const override {
    return joy_->GetJoy(age, shocks, fitness, investment) +
           shift_->GetShift(shocks, fitness);
  };

 private:
  std::shared_ptr<const Joy> joy_;
  std::shared_ptr<const Shifter> shift_;
};

}  // namespace joy
}  // namespace healthcare

#endif  // HEALTHCARE_JOY_SHIFT_DECORATOR_H_
