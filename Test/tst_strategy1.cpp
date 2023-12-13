#include <gtest/gtest.h>

#include <GraphData.h>
#include <Repository.h>

// Demonstrate some basic assertions.
TEST(Strategy1, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);

    GraphData data = Repository().LoadFile("ding").graphData;
}
