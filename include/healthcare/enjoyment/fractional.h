#ifndef _HEALTHCARE_ENJOYMENT_FRACTIONAL_H_
#define _HEALTHCARE_ENJOYMENT_FRACTIONAL_H_

#include "healthcare/enjoyment.h"

namespace healthcare {
namespace enjoyment {

class Fractional : public Enjoyment {
 public:
  Fractional(double j, int max_shocks, double shock_emph_ = 1);
  double GetEnjoyment(int shocks, int life_investment) const override;

 private:
  double j_;
  int max_shocks_;
  double shock_emph_;
};

}  // namespace enjoyment
}  // namespace healthcare
#endif  // _HEALTHCARE_ENJOYMENT_FRACTIONAL_H_
