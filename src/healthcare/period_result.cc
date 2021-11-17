#include "healthcare/period_result.h"

namespace healthcare {

std::ostream& operator<<(std::ostream& os, const PeriodResult& pr) {
  return os << pr.joy << "," << pr.person << "," << pr.probability << ","
            << "," << pr.subj_prob << "," << pr.shock_prob << ","
            << pr.subj_no_shock_prob << "," << pr.subj_shock_prob
            << ","
            // << pr.death_prob << "," << pr.subj_no_death_prob << ","
            << pr.immediate_utility << "," << pr.future_utility << ","
            << pr.utility;
}

};  // namespace healthcare
