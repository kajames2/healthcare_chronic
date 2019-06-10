#include <gtest/gtest.h>
#include "healthcare/insurance/actuarial.h"
#include "healthcare/probability/gompertz_shocks.h"

class ActuarialTest : public ::testing::Test {
 public:
  ActuarialTest() {}
};

class FlatProb : public healthcare::Probability {
 public:
  float GetProbability(int age, int shocks, int fitness) const override {
    return 0.5;
  }
};

TEST_F(ActuarialTest, equaltest) {
  auto prob = std::make_shared<FlatProb>();
  healthcare::insurance::Actuarial f(1.1, 0, 100, prob);
  float total = f.GetPrice(5, 2, 10);
  EXPECT_NEAR(total, 55, 0.00001);
}
