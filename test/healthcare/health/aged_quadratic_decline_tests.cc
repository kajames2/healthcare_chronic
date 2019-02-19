#include <gtest/gtest.h>
#include "healthcare/health/aged_quadratic_decline.h"

class AgedQuadraticDeclineTest : public::testing::Test {
public:
    AgedQuadraticDeclineTest() {}
};
// a problem about the output
TEST_F(AgedQuadraticDeclineTest, equaltest) {
    healthcare::health::AgedQuadraticDecline f(0.1, 0.1, 0.1, 0.1);
    float rl = f.GetHealth(10, 2, 0.1);
    EXPECT_FLOAT_EQ(0.241, rl);
}
