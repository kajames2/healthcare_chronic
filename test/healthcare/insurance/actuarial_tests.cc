#include <gtest/gtest.h>
#include "healthcare/insurance/actuarial.h"
#include "healthcare/prob_func.h"

class ActuarialTest : public ::testing::Test {
 public:
  ActuarialTest() {}
};

TEST_F(ActuarialTest, equaltest) {
  auto prob = [](unsigned int, unsigned int, unsigned int) { return 0.5; };
  healthcare::insurance::Actuarial f(1.1f, 0, 100, prob);
  float total = f.GetPrice(5, 2, 10);
  EXPECT_NEAR(total, 55, 0.00001);
}
