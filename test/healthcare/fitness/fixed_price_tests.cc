#include <gtest/gtest.h>
#include "healthcare/fitness/fixed_price.h"

class FixedPriceTest : public::testing::Test {
public:
    FixedPriceTest() {}
};

TEST_F(FixedPriceTest, equaltest) {
    healthcare::fitness::FixedPrice pl(9);
    int rl = pl.GetFitness(0, 0);
    int r2 = pl.GetFitnessCost(0, 0);
    EXPECT_EQ(0,  rl);
    EXPECT_EQ(0,  r2);
}
