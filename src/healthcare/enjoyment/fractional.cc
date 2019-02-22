#include "healthcare/enjoyment/fractional.h"

#include <algorithm>
#include <boost/math/constants/constants.hpp>

namespace healthcare {
namespace enjoyment {
Fractional::Fractional(double j, int max_shocks, double shock_emph)
    : j_(j), max_shocks_(max_shocks), shock_emph_(shock_emph) {}

double Fractional::GetEnjoyment(int shocks, int life_investment) const {
  static const double pi = boost::math::constants::pi<double>();
  double base_enjoyment = life_investment / (life_investment + j_);
  double shock_penalty = shock_emph_ * std::sqrt(std::cos(pi/(2 * max_shocks_)*shocks));
  return shock_penalty * base_enjoyment;
}

}  // namespace enjoyment
}  // namespace healthcare
