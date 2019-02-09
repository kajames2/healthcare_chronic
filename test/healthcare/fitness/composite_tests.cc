#include <gtest/gtest.h>
#include "healthcare/fitness/composite.h"
#include "healthcare/fitness.h"
#include "healthcare/fitness/proportional_loss.h"

#include <memory>

class CompositeTest : public::testing::Test {
public:
    CompositeTest() {}
};
// wrong in composite function
TEST_F(CompositeTest, equaltest) {
    std::vector<std::shared_ptr<const healthcare::Fitness>> fits;
    fits.push_back(std::make_shared<healthcare::fitness::ProportionalLoss>(0.2));
    fits.push_back(std::make_shared<healthcare::fitness::ProportionalLoss>(0.3));
    healthcare::fitness::Composite pl(100, 10, fits);
    int rl = pl.GetFitness(0, 0);
    int r2 = pl.GetFitnessCost(0, 0);
    EXPECT_EQ(0,  rl);
    EXPECT_EQ(0,  r2);
}
