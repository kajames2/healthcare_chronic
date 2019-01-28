#include <gtest/gtest.h>
#include "healthcare/enjoyment/shocks_fractional.h"

class ShocksFractionalTest : public::testing::Test {
public:
    ShocksFractionalTest() {}
};
// wrong in composite function
TEST_F(ShocksFractionalTest, equaltest) {
    healthcare::enjoyment::ShocksFractional pl(1.0, 1.0);
    double r = pl.GetEnjoyment(0, 0, 0);
    EXPECT_EQ(0,  r);
}
