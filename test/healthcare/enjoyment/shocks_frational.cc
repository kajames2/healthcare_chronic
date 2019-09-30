#include <gtest/gtest.h>
#include "healthcare/enjoyment/shocks_fractional.h"

class ShocksFractionalTest : public::testing::Test {
public:
    ShocksFractionalTest() {}
};
// wrong in composite function
TEST_F(ShocksFractionalTest, equaltest) {
    healthcare::enjoyment::ShocksFractional pl(0, 0.5);
    double r = pl.GetEnjoyment(0.5, 1, 10);
    EXPECT_EQ(0.95,  r);
}
