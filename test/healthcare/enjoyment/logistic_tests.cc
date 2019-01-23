#include <gtest/gtest.h>

#include <memory>

#include "healthcare/enjoyment/logistic.h"

namespace enjoymenttests {

class EnjoymentLogisticTest : public ::testing::Test {
 public:
  EnjoymentLogisticTest() : health_(0), life_investment_(0), enjoyment_() {}

 protected:
  virtual void SetUp() {
    health_ = 80;
    life_investment_ = 20;
    enjoyment_ = std::make_unique<healthcare::enjoyment::Logistic>(0.05);
  }

  int health_;
  int life_investment_;
  std::unique_ptr<healthcare::enjoyment::Logistic> enjoyment_;
};

TEST_F(EnjoymentLogisticTest, GetEnjoyment) {
  ASSERT_DOUBLE_EQ(58.48468629040039,
                   enjoyment_->GetEnjoyment(health_, life_investment_));
}

}  // namespace enjoymenttests
