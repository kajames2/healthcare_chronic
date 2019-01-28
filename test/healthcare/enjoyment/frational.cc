#include <gtest/gtest.h>
#include "healthcare/enjoyment/fractional.h"

class FractionalTest : public::testing::Test {
public:
    FractionalTest() {}
};
// wrong in composite function
TEST_F(FractionalTest, equaltest) {
    healthcare::enjoyment::Fractional pl(1.0);
    double r = pl.GetEnjoyment(0, 0, 0);
    EXPECT_EQ(0,  r);
}
