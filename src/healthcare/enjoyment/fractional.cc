#include "healthcare/enjoyment/fractional.h"

namespace healthcare {
namespace enjoyment {
Fractional::Fractional(double j)
    : j_(j) {}

double Fractional::GetEnjoyment(int shocks, int life_investment) const {
  return life_investment / (life_investment + j_);
}

}  // namespace enjoyment
}  // namespace healthcare
