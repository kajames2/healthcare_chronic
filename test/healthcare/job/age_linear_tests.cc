#include <gtest/gtest.h>
#include "healthcare/job/age_linear.h"

class AgeLinearTest : public::testing::Test {
public:
    AgeLinearTest() {}
};

TEST_F(AgeLinearTest, equaltest) {
    healthcare::job::AgeLinear al(10.6, 1.0);
    int rl = al.GetEarnings(10);
    EXPECT_EQ(21,  rl);
}
