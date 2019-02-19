#include <gtest/gtest.h>
#include "healthcare/fitness/fixed_price.h"

class FixedPriceTest : public::testing::Test {
public:
    FixedPriceTest() {}
};

TEST_F(FixedPriceTest, equaltest) {
    healthcare::fitness::FixedPrice pl(10);
    int rl = pl.GetFitness(10, 10);
    int r2 = pl.GetFitnessCost(2, 5);
    EXPECT_EQ(11,  rl);
    EXPECT_EQ(30,  r2);
}
