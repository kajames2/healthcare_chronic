#include <gtest/gtest.h>
#include "healthcare/insurance/actuarial.h"

class ActuarialTest : public::testing::Test {
public:
    ActuarialTest() {}
};

TEST_F(ActuarialTest, equaltest) {
    healthcare::insurance::Actuarial f(0.4, 2, 0.3);
    float total = f.GetPrice(10, 0.8);
    EXPECT_EQ(total, 10);
}
