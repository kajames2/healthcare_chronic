#ifndef HEALTHCARE_JOY_FRACTIONAL_H_
#define HEALTHCARE_JOY_FRACTIONAL_H_

#include "healthcare/joy.h"

namespace healthcare {
namespace joy {

class Fractional : public Joy {
 public:
  explicit Fractional(double j);
  double GetJoy(int shocks, int life_investment) const override;

 private:
  double j_;
};

}  // namespace joy
}  // namespace healthcare
#endif  // HEALTHCARE_JOY_FRACTIONAL_H_
