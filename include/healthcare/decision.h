#ifndef HEALTHCARE_DECISION_H_
#define HEALTHCARE_DECISION_H_

#include <ostream>

namespace healthcare {

struct Decision {
  unsigned int fitness_spending = 0;
  unsigned int joy_spending = 0;
  unsigned int insurance_spending = 0;
  bool buy_insurance = false;
};

unsigned int TotalSpending(Decision dec);

std::ostream& operator<<(std::ostream& out, const Decision& d);
}  // namespace healthcare
#endif  // HEALTHCARE_DECISION_H_
