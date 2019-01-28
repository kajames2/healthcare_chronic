#include <gtest/gtest.h>
#include "healthcare/health/quadratic_decline.h"

class QuadraticDeclineTest : public::testing::Test {
public:
    QuadraticDeclineTest() {}
};

TEST_F(QuadraticDeclineTest, equaltest) {
    healthcare::health::QuadraticDecline f(0.0, 0.0, 0.0, 0.0);
    float rl = f.GetHealth(0, 0, 0);
    EXPECT_NE(0, rl);
}
