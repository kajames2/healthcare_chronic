#include <gtest/gtest.h>
#include "healthcare/fitness/flat_loss.h"

class FlatLossTest : public::testing::Test {
public:
    FlatLossTest() {}
};

TEST_F(FlatLossTest, equaltest) {
    healthcare::fitness::FlatLoss pl(9);
    int rl = pl.GetFitness(10, 0);
    int r2 = pl.GetFitnessCost(0, 0);
    EXPECT_EQ(1,  rl);
    EXPECT_EQ(0,  r2);
}
