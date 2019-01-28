#include <gtest/gtest.h>
#include "healthcare/fitness/proportional_loss.h"

class ProportionalLossTest : public::testing::Test {
public:
    ProportionalLossTest() {}
};

TEST_F(ProportionalLossTest, equaltest) {
    healthcare::fitness::ProportionalLoss pl(0.0);
    int rl = pl.GetFitness(0, 0);
    int r2 = pl.GetFitnessCost(0, 0);
    EXPECT_EQ(0,  rl);
    EXPECT_EQ(0,  r2);
}
