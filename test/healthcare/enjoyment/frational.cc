#include <gtest/gtest.h>
#include "healthcare/enjoyment/fractional.h"

class FractionalTest : public::testing::Test {
public:
    FractionalTest() {}
};
// wrong in composite function
TEST_F(FractionalTest, equaltest) {
  healthcare::enjoyment::Fractional pl(60);
  double r = pl.GetEnjoyment(1, 60);
  EXPECT_NEAR(0.5, r, 0.0001);
}
