#ifndef HEALTHCARE_MODIFIER_LINEAR_H_
#define HEALTHCARE_MODIFIER_LINEAR_H_

#include "healthcare/modifier/single_type.h"

namespace healthcare {
namespace modifier {

class Linear : public SingleType {
 public:
  Linear(Param param, Func func, float max_modification, int max_param)
      : SingleType(param, func),
        max_modification_(max_modification),
        max_param_(max_param) {}
  float GetModification(int param) const override {
    return (1 - max_modification_) + max_modification_ * param / max_param_;
  }

  int max_param_;
  float max_modification_;
};

}  // namespace modifier
}  // namespace healthcare

#endif  // HEALTHCARE_MODIFIER_LINEAR_H_
