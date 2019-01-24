#ifndef _HEALTHCARE_PERSON_INCOME_H_
#define _HEALTHCARE_PERSON_INCOME_H_

#include "healthcare/person.h"

namespace healthcare {

struct PersonIncome : public Person {
  int budget;
  int income;
};

}  // namespace healthcare

#endif  // _HEALTHCARE_PERSON_INCOME_H_
