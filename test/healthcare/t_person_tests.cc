#include <gtest/gtest.h>
#include "healthcare/person.h"

class TPersonTest : public ::testing::Test {
public:
  TPersonTest() {}
};

TEST_F(TPersonTest, equaltest) {
    healthcare::Person p1;
    p1.age = 30;
    p1.shocks = 10;
    p1.fitness = 20;
    p1.cash = 100;
    healthcare::Person p2(p1);
    EXPECT_TRUE(p1 == p2);
    p2.age = 29;
    EXPECT_FALSE(p1 == p2);
}
