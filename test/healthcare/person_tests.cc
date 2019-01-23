#include <gtest/gtest.h>

#include <memory>

#include "healthcare/enjoyment/fractional.h"
#include "healthcare/degeneration/linear.h"
#include "healthcare/job/flat.h"
#include "healthcare/person.h"
#include "healthcare/regeneration/fractional.h"

class PersonTest : public ::testing::Test {
 public:
  PersonTest() : state_(), state_wounded_() {}

 protected:
  virtual void SetUp() {
    state_ = healthcare::Person{2, 80, 20};
    state_ = healthcare::Person{5, 5, 50};
  }

  healthcare::Person state_, state_wounded_;
};
