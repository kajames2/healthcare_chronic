#ifndef HEALTHCARE_PROBABILITY_MOD_DECORATOR_H_
#define HEALTHCARE_PROBABILITY_MOD_DECORATOR_H_

#include <memory>

#include "healthcare/modulator.h"
#include "healthcare/probability.h"

namespace healthcare {
namespace probability {

class ModDecorator : public Probability {
 public:
  ModDecorator(std::shared_ptr<const Probability> prob,
               std::shared_ptr<const Modulator> mod)
      : prob_(prob), mod_(mod) {}
  float GetProbability(int age, int shocks, int fitness) const override {
    return prob_->GetProbability(age, shocks, fitness) *
           mod_->GetModulation(shocks, fitness);
  };

 private:
  std::shared_ptr<const Probability> prob_;
  std::shared_ptr<const Modulator> mod_;
};

}  // namespace probability
}  // namespace healthcare

#endif  // HEALTHCARE_PROBABILITY_MOD_DECORATOR_H_
