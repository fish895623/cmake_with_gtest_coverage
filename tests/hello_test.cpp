#include "hello.hpp"
#include <gtest/gtest.h>

TEST(HelloTest, Teins) {
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}

TEST(hellotesting, zine) { EXPECT_EQ(add(1, 2), 3); }
