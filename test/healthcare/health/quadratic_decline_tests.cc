#include <gtest/gtest.h>
#include "healthcare/health/quadratic_decline.h"

class QuadraticDeclineTest : public::testing::Test {
public:
    QuadraticDeclineTest() {}
};
//change is made with the test value.
TEST_F(QuadraticDeclineTest, equaltest) {
    healthcare::health::QuadraticDecline f(0.1, 0.1, 0.1, 0.1);
    float rl = f.GetHealth(30, 0, 0.876);
    EXPECT_FLOAT_EQ(0.8, rl);
}
