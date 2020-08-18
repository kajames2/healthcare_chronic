#include <gtest/gtest.h>
#include "healthcare/insurance/actuarial.h"

class ActuarialTest : public ::testing::Test {
 public:
  ActuarialTest() {}
};

TEST_F(ActuarialTest, equaltest) {
  auto prob = [](int, int, int) { return 0.5; };
  healthcare::insurance::Actuarial f(1.1, 0, 100, prob);
  float total = f.GetPrice(5, 2, 10);
  EXPECT_NEAR(total, 55, 0.00001);
}
