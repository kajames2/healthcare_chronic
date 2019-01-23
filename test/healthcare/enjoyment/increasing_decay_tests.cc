#include <gtest/gtest.h>

#include <memory>

#include "healthcare/enjoyment/increasing_decay.h"

class EnjoymentIncreasingDecayTest : public ::testing::Test {
 public:
  EnjoymentIncreasingDecayTest()
      : health_(0), life_investment_(0), enjoyment_() {}

 protected:
  virtual void SetUp() {
    health_ = 80;
    life_investment_ = 20;
    enjoyment_ = std::make_unique<healthcare::enjoyment::IncreasingDecay>(
        0.05, 0.3, 50);
  }

  int health_;
  int life_investment_;
  std::unique_ptr<healthcare::enjoyment::IncreasingDecay> enjoyment_;
};

TEST_F(EnjoymentIncreasingDecayTest, GetEnjoyment) {
  ASSERT_DOUBLE_EQ(29.70966626494221,
                   enjoyment_->GetEnjoyment(health_, life_investment_));
}
