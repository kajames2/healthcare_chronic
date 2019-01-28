#include <gtest/gtest.h>
#include "healthcare/fitness/composite.h"

class CompositeTest : public::testing::Test {
public:
    CompositeTest() {}
};
// wrong in composite function
TEST_F(CompositeTest, equaltest) {
    healthcare::fitness::Composite pl(1, 1, {10, 10});
    int rl = pl.GetFitness(0, 0);
    int r2 = pl.GetFitnessCost(0, 0);
    EXPECT_EQ(0,  rl);
    EXPECT_EQ(0,  r2);
}
