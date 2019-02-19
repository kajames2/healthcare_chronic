#include <gtest/gtest.h>
#include "healthcare/insurance/fixed.h"

class FixedTest : public::testing::Test {
public:
    FixedTest() {}
};

TEST_F(FixedTest, equaltest) {
    healthcare::insurance::Fixed f(10);
    float total = f.GetPrice(10, 0.8);
    EXPECT_EQ(total, 10);
}
