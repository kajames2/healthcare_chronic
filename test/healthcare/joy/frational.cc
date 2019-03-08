#include <gtest/gtest.h>
#include "healthcare/joy/fractional.h"

class FractionalTest : public ::testing::Test {
 public:
  FractionalTest() {}
};
// wrong in composite function
TEST_F(FractionalTest, equaltest) {
  healthcare::joy::Fractional pl(60);
  double r = pl.GetJoy(1, 60);
  EXPECT_NEAR(0.5, r, 0.0001);
}
