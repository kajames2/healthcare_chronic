#include "healthcare/decision.h"

#include <ostream>

namespace healthcare {

unsigned int TotalSpending(Decision dec) {
  return dec.joy_spending + dec.fitness_spending + dec.insurance_spending;
}

std::ostream& operator<<(std::ostream& out, const Decision& d) {
  return out << d.fitness_spending << "," << d.joy_spending << ","
             << d.insurance_spending << "," << d.buy_insurance;
}

}  // namespace healthcare
