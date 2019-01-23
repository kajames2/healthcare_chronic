#include <gtest/gtest.h>

#include <memory>

#include "healthcare/degeneration/linear.h"

namespace degenerationtests {

class DegenerationLinearTest : public ::testing::Test {
 public:
  DegenerationLinearTest() : degen_() {}

 protected:
  virtual void SetUp() {
    degen_ = std::make_unique<healthcare::degeneration::Linear>(10, 3);
  }

  int age_;
  std::unique_ptr<healthcare::degeneration::Linear> degen_;
};

TEST_F(DegenerationLinearTest, GetDegeneration) {
  ASSERT_EQ(22, degen_->GetDegeneration(4, 10));
}

}  // namespace degenerationtests
