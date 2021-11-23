#ifndef HEALTHCARE_PERSON_INCOME_H_
#define HEALTHCARE_PERSON_INCOME_H_

#include "healthcare/person.h"

namespace healthcare {

struct PersonIncome : public Person {
  unsigned int budget;
  int income;
};

}  // namespace healthcare

#endif  // HEALTHCARE_PERSON_INCOME_H_
