#ifndef _HEALTHCARE_DECISION_H_
#define _HEALTHCARE_DECISION_H_

#include <ostream>

namespace healthcare {

struct Decision {
  int fitness_spending = 0;
  int joy_spending = 0;
  int insurance_spending = 0;
};

int TotalSpending(Decision dec);

std::ostream& operator<<(std::ostream& out, const Decision& d);
}  // namespace healthcare
#endif  // _HEALTHCARE_DECISION_H_
