#include <gtest/gtest.h>
#include "healthcare/decision.h"

class DecisionTest : public::testing::Test {
public:
    DecisionTest() {}
};

TEST_F(DecisionTest, equaltest) {
    healthcare::Decision d1{10, 30, 40};
    int total = TotalSpending(d1);
    EXPECT_EQ(total, 80);
}
