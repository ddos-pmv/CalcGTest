#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <limits>

#include "IHistory.h"
#include "SimpleCalculator.h"

namespace calc::tests {

class IHistoryMock : public IHistory {
 public:
  MOCK_METHOD(void, AddEntry, (const std::string&), (override));
  MOCK_METHOD(std::vector<std::string>, GetLastOperations, (size_t),
              (const, override));
};

class EdgeCaseTest : public ::testing::Test {
 protected:
  IHistoryMock m_history;
  SimpleCalculator m_calc{m_history};
};

TEST_F(EdgeCaseTest, AddWithMaxValues) {
  int a = std::numeric_limits<int>::max();
  int b = -1;

  EXPECT_CALL(m_history, AddEntry("2147483647 + -1 = 2147483646"));
  ASSERT_EQ(m_calc.Add(a, b), a + b);
}

TEST_F(EdgeCaseTest, SubtractWithMinValues) {
  int a = std::numeric_limits<int>::min();
  int b = 1;

  // Осторожно: a - b может выйти за границы int
  // Проверим поведение (может быть UB без проверки в коде)
  long long expected = static_cast<long long>(a) - b;

  std::ostringstream expectedEntry;
  expectedEntry << a << " - " << b << " = " << expected;

  EXPECT_CALL(m_history, AddEntry(expectedEntry.str()));
  ASSERT_EQ(static_cast<long long>(m_calc.Subtract(a, b)), expected);
}

}  // namespace calc::tests
