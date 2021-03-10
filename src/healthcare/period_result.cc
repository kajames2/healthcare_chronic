#include "healthcare/period_result.h"

namespace healthcare {

std::ostream& operator<<(std::ostream& os, const PeriodResult& pr) {
  return os << pr.joy << "," << pr.person << "," << pr.probability << ","
            << pr.immediate_utility << "," << pr.future_utility << ","
            << pr.utility;
}

};  // namespace healthcare
