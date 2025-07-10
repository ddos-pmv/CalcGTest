#include <gtest/gtest.h>

#include "InMemoryHistory.h"

namespace calc::tests {

class InMemoryHistoryTest : public ::testing::Test {
 protected:
  InMemoryHistory history;
};

TEST_F(InMemoryHistoryTest, AddEntryStoresCorrectly) {
  history.AddEntry("1 + 1 = 2");
  history.AddEntry("2 * 2 = 4");

  auto result = history.GetLastOperations(2);

  ASSERT_EQ(result.size(), 2);
  EXPECT_EQ(result[0], "1 + 1 = 2");
  EXPECT_EQ(result[1], "2 * 2 = 4");
}

TEST_F(InMemoryHistoryTest, GetLessThanAdded) {
  history.AddEntry("1 + 1 = 2");
  history.AddEntry("2 * 2 = 4");
  history.AddEntry("3 - 1 = 2");

  auto result = history.GetLastOperations(2);

  ASSERT_EQ(result.size(), 2);
  EXPECT_EQ(result[0], "2 * 2 = 4");
  EXPECT_EQ(result[1], "3 - 1 = 2");
}

TEST_F(InMemoryHistoryTest, GetMoreThanAvailable) {
  history.AddEntry("1 + 1 = 2");

  auto result = history.GetLastOperations(10);
  ASSERT_EQ(result.size(), 1);
  EXPECT_EQ(result[0], "1 + 1 = 2");
}

TEST_F(InMemoryHistoryTest, EmptyHistoryReturnsEmptyVector) {
  auto result = history.GetLastOperations(5);
  ASSERT_TRUE(result.empty());
}

TEST_F(InMemoryHistoryTest, OrderIsPreserved) {
  history.AddEntry("1 + 1 = 2");
  history.AddEntry("2 + 2 = 4");
  history.AddEntry("3 + 3 = 6");

  auto result = history.GetLastOperations(3);

  ASSERT_EQ(result.size(), 3);
  EXPECT_EQ(result[0], "1 + 1 = 2");
  EXPECT_EQ(result[1], "2 + 2 = 4");
  EXPECT_EQ(result[2], "3 + 3 = 6");
}

}  // namespace calc::tests
