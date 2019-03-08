#ifndef HEALTHCARE_PROBABILITY_GOMPERTZ_MAKEHAM_H_
#define HEALTHCARE_PROBABILITY_GOMPERTZ_MAKEHAM_H_

#include <cmath>

#include "healthcare/probability.h"

namespace healthcare {
namespace probability {

class GompertzMakeham : public Probability {
 public:
  GompertzMakeham(float lambda, float alpha, float beta)
      : lambda_(lambda), alpha_(alpha), beta_(beta) {}
  float GetProbability(int age, int shocks, int fitness) const override {
    return lambda_ + alpha_ * std::exp(beta_ * age);
  }

 private:
  float lambda_;
  float alpha_;
  float beta_;
};

}  // namespace probability
}  // namespace healthcare

#endif  // HEALTHCARE_PROBABILITY_GOMPERTZ_MAKEHAM_H_
