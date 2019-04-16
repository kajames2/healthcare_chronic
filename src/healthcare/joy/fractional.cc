#include "healthcare/joy/fractional.h"

namespace healthcare {
namespace joy {

Fractional::Fractional(double j) : j_(j) {}

double Fractional::GetJoy(int age, int shocks, int fitness,
                          int investment) const {
  return investment / (investment + j_);
}

}  // namespace joy
}  // namespace healthcare
