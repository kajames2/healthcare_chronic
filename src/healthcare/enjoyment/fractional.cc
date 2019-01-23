#include "healthcare/enjoyment/fractional.h"

#include <algorithm>

namespace healthcare {
namespace enjoyment {

Fractional::Fractional(double j, int max_shocks, double shock_emph)
    : j_(j), max_shocks_(max_shocks), shock_emph_(shock_emph) {}

double Fractional::GetEnjoyment(int shocks, int life_investment) const {
  double base_enjoyment = life_investment / (life_investment + j_);
  double shock_penalty = shock_emph_ * shocks / static_cast<double>(max_shocks_);
  return (1 - shock_penalty) * base_enjoyment;
}

}  // namespace enjoyment
}  // namespace healthcare
