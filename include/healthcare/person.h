#ifndef HEALTHCARE_PERSON_H_
#define HEALTHCARE_PERSON_H_

#include <ostream>

namespace healthcare {
struct Person {
  unsigned int age = 0;
  unsigned int shocks = 0;
  unsigned int fitness = 0;
  int cash = 0;
};

bool operator==(const Person& lhs, const Person& rhs);
std::ostream& operator<<(std::ostream& out, const Person& p);

}  // namespace healthcare
#endif  // HEALTHCARE_PERSON_H_
