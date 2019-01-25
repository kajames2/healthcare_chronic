#include <gtest/gtest.h>
#include "healthcare/job/flat.h"

class FlatTest : public ::testing::Test {
public:
  FlatTest() {}
};

Test_F(FlatTest, equaltest) {
    healthcare::job::Flat new(10);
    int rate = new.GetEarnings(30, 50.0);
    EXPECT_EQ(rate, 10);
}
