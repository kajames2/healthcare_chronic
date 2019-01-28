#include <gtest/gtest.h>
#include "healthcare/health/aged_quadratic_decline.h"

class AgedQuadraticDeclineTest : public::testing::Test {
public:
    AgedQuadraticDeclineTest() {}
};

TEST_F(AgedQuadraticDeclineTest, equaltest) {
    healthcare::health::AgedQuadraticDecline f(0.0, 0.0, 0.0, 0.0);
    float rl = f.GetHealth(0, 0, 0);
    EXPECT_NE(0, rl);
}
