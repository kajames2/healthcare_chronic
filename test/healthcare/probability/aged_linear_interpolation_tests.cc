#include <gtest/gtest.h>
#include "healthcare/probability/aged_linear_interpolation.h"

class AgedLinearInterpolationTest : public::testing::Test {
public:
    AgedLinearInterpolationTest() {}
};

TEST_F(AgedLinearInterpolationTest, equaltest) {
    healthcare::probability::AgedLinearInterpolation ls(0.0, 0.0);
    float rl = ls(10, 1.0);
    EXPECT_NE(0.0,  rl);
}
