#include "healthcare/joy/fractional.h"

namespace healthcare {
namespace joy {

Fractional::Fractional(double j) : j_(j) {}

double Fractional::GetJoy(int shocks, int life_investment) const {
  return life_investment / (life_investment + j_);
}

}  // namespace joy
}  // namespace healthcare
