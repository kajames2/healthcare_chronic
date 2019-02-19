#include <gtest/gtest.h>
#include "healthcare/probability/linear_interpolation.h"

class LinearInterpolationTest : public::testing::Test {
public:
    LinearInterpolationTest() {}
};

TEST_F(LinearInterpolationTest, equaltest) {
    healthcare::probability::LinearInterpolation ls(0.1, 0.2);
    float rl = ls(10, 1.0);
    EXPECT_NE(0.1,  rl);
}
