#include <gtest/gtest.h>
#include "healthcare/fitness/proportional_loss.h"

class ProportionalLossTest : public::testing::Test {
public:
    ProportionalLossTest() {}
};

// update the test
TEST_F(ProportionalLossTest, equaltest) {
    healthcare::fitness::ProportionalLoss pl(0.5);
    int rl = pl.GetFitness(10, 10);
    int r2 = pl.GetFitnessCost(10, 0);
    EXPECT_EQ(5,  rl);
    EXPECT_EQ(10000,  r2);
}
