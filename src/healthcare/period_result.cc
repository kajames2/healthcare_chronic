#include "healthcare/period_result.h"

namespace healthcare {

std::ostream& operator<<(std::ostream& os, const PeriodResult& pr) {
  return os << pr.joy << "," << pr.person << "," << pr.probability << ","
            << pr.future_value << "," << pr.value;
}

};  // namespace healthcare
