#include <gtest/gtest.h>
#include "healthcare/job/flat.h"

class FlatTest : public::testing::Test {
public:
    FlatTest() {}
};

TEST_F(FlatTest, equaltest) {
    healthcare::job::Flat f(3);
    int rl = f.GetEarnings(10, 1.0);
    EXPECT_EQ(3,  rl);
}
