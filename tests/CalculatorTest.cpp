#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "IHistory.h"
#include "SimpleCalculator.h"

namespace calc::tests {

class IHistoryMock : public IHistory {
 public:
  MOCK_METHOD(void, AddEntry, (const std::string&), (override));
  MOCK_METHOD(std::vector<std::string>, GetLastOperations, (size_t),
              (const, override));
};

class CalculationHistoryTest : public ::testing::Test {
 protected:
  IHistoryMock m_history;
  SimpleCalculator m_calc{m_history};
};

TEST_F(CalculationHistoryTest, BasicAddition) {
  EXPECT_CALL(m_history, AddEntry("2 + 2 = 4"));
  ASSERT_EQ(m_calc.Add(2, 2), 4);

  EXPECT_CALL(m_history, AddEntry("5 + 4 = 9"));
  ASSERT_EQ(m_calc.Add(5, 4), 9);
}

TEST_F(CalculationHistoryTest, Subtraction) {
  EXPECT_CALL(m_history, AddEntry("5 - 3 = 2"));
  ASSERT_EQ(m_calc.Subtract(5, 3), 2);

  EXPECT_CALL(m_history, AddEntry("10 - 7 = 3"));
  ASSERT_EQ(m_calc.Subtract(10, 7), 3);
}

TEST_F(CalculationHistoryTest, Multiplication) {
  EXPECT_CALL(m_history, AddEntry("3 * 4 = 12"));
  ASSERT_EQ(m_calc.Multiply(3, 4), 12);

  EXPECT_CALL(m_history, AddEntry("5 * 6 = 30"));
  ASSERT_EQ(m_calc.Multiply(5, 6), 30);
}

TEST_F(CalculationHistoryTest, Division) {
  EXPECT_CALL(m_history, AddEntry("10 / 2 = 5"));
  ASSERT_EQ(m_calc.Divide(10, 2), 5);

  EXPECT_CALL(m_history, AddEntry("15 / 3 = 5"));
  ASSERT_EQ(m_calc.Divide(15, 3), 5);
}

TEST_F(CalculationHistoryTest, HistoryRetrieval) {
  EXPECT_CALL(m_history, AddEntry("2 + 2 = 4"));
  EXPECT_CALL(m_history, AddEntry("5 * 6 = 30"));
  EXPECT_CALL(m_history, AddEntry("10 / 2 = 5"));

  m_calc.Add(2, 2);
  m_calc.Multiply(5, 6);
  m_calc.Divide(10, 2);

  EXPECT_CALL(m_history, GetLastOperations(2))
      .WillOnce(::testing::Return(
          std::vector<std::string>{"5 * 6 = 30", "10 / 2 = 5"}));

  auto hist = m_history.GetLastOperations(2);
  ASSERT_EQ(hist.size(), 2);
  ASSERT_EQ(hist[0], "5 * 6 = 30");
  ASSERT_EQ(hist[1], "10 / 2 = 5");
}

}  // namespace calc::tests