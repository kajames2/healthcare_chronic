#include <gtest/gtest.h>

#include <memory>

#include "healthcare/job/flat.h"

namespace jobtests {

class JobFlatTest : public ::testing::Test {
 public:
  JobFlatTest() : job_() {}

 protected:
  virtual void SetUp() { job_ = std::make_unique<healthcare::job::Flat>(85); }

  std::unique_ptr<healthcare::job::Flat> job_;
};

TEST_F(JobFlatTest, GetEarnings) {
  ASSERT_DOUBLE_EQ(85, job_->GetEarnings(1, 60));
  ASSERT_DOUBLE_EQ(85, job_->GetEarnings(10, 60));
}

}  // namespace jobtests
