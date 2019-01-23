#include <gtest/gtest.h>

#include <memory>

#include "healthcare/enjoyment/fractional.h"

namespace enjoymenttests {

class EnjoymentFractionalTest : public ::testing::Test {
 public:
  EnjoymentFractionalTest()
      : health_(0), life_investment_(0), enjoyment_() {}

 protected:
  virtual void SetUp() {
    health_ = 80;
    life_investment_ = 20;
    enjoyment_ = std::make_unique<healthcare::enjoyment::Fractional>(30);
  }

  int health_;
  int life_investment_;
  std::unique_ptr<healthcare::enjoyment::Fractional> enjoyment_;
};

TEST_F(EnjoymentFractionalTest, GetEnjoyment) {
  ASSERT_DOUBLE_EQ(32,
                   enjoyment_->GetEnjoyment(health_, life_investment_));
}

}  // namespace enjoymenttests
