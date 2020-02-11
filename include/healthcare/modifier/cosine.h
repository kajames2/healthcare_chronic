#ifndef HEALTHCARE_MODIFIER_COSINE_H_
#define HEALTHCARE_MODIFIER_COSINE_H_

#include <cmath>

#include <boost/math/constants/constants.hpp>
#include "healthcare/modifier.h"

namespace healthcare {
namespace modifier {

class Cosine : public Modifier {
 public:
  Cosine(Param param, Func func, float max_modification, int max_param)
      : Modifier(param, func),
        max_param_(max_param),
        max_modification_(max_modification) {}
  float GetModification(int param) const override {
    static const double pi = boost::math::constants::pi<double>();
    return max_modification_ *
           std::sqrt(std::cos(pi / (2 * max_param_) * param));
  }

  int max_param_;
  float max_modification_;
};

}  // namespace modifier
}  // namespace healthcare

#endif  // HEALTHCARE_MODIFIER_COSINE_H_
