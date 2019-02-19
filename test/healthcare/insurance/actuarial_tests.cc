#include <gtest/gtest.h>
#include "healthcare/insurance/actuarial.h"
#include "healthcare/probability/linear_interpolation.h"

class ActuarialTest : public::testing::Test {
public:
    ActuarialTest() {}
};

TEST_F(ActuarialTest, equaltest) {
//    healthcare::probability::LinearInterpolation l;
    auto prob = std::make_shared<healthcare::probability::LinearInterpolation>(0.2, 0.8);
    healthcare::insurance::Actuarial f(4.5, 2, prob);
    float total = f.GetPrice(10, 0.5);
    EXPECT_EQ(total, 5);
}
