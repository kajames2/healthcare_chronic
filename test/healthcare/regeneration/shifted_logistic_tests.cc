#include <gtest/gtest.h>

#include <memory>

#include "healthcare/regeneration/shifted_logistic.h"

namespace regenerationtests {

class RegenerationShiftedLogisticTest : public ::testing::Test {
 public:
  RegenerationShiftedLogisticTest()
      : health_(0), health_investment_(0), regen_() {}

 protected:
  virtual void SetUp() {
    health_ = 80;
    health_investment_ = 20;
    regen_ = std::make_unique<healthcare::regeneration::ShiftedLogistic>(0.02);
  }

  int health_;
  int health_investment_;
  std::unique_ptr<healthcare::regeneration::ShiftedLogistic> regen_;
};

TEST_F(RegenerationShiftedLogisticTest, GetRegeneration) {
  ASSERT_DOUBLE_EQ(5, regen_->GetHealthRegained(health_, health_investment_));
}

}  // namespace regenerationtests
