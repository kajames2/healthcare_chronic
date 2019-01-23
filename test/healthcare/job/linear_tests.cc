#include <gtest/gtest.h>

#include <memory>

#include "healthcare/job/linear.h"

namespace jobtests {

class JobLinearTest : public ::testing::Test {
 public:
  JobLinearTest() : job_() {}

 protected:
  virtual void SetUp() {
    job_ = std::make_unique<healthcare::job::Linear>(0.75);
  }

  std::unique_ptr<healthcare::job::Linear> job_;
};

TEST_F(JobLinearTest, GetEarnings) {
  ASSERT_DOUBLE_EQ(45, job_->GetEarnings(1, 60));
  ASSERT_DOUBLE_EQ(45, job_->GetEarnings(10, 60));
}

}  // namespace jobtests
