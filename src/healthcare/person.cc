#include "healthcare/person.h"

#include <ostream>

namespace healthcare {

bool operator==(const Person& lhs, const Person& rhs) {
  return lhs.age == rhs.age && lhs.shocks == rhs.shocks &&
         lhs.fitness == rhs.fitness && lhs.cash == rhs.cash;
}

std::ostream& operator<<(std::ostream& out, const Person& p) {
  return out << p.age << "," << p.shocks << "," << p.fitness << "," << p.cash;
}

}  // namespace healthcare
