// (C) PROTEI protei.com

#include "SimpleCalculator.h"

#include <sstream>

#include "IHistory.h"

namespace calc {

SimpleCalculator::SimpleCalculator(IHistory& history) : m_history(history) {}

void SimpleCalculator::SetHistory(IHistory& history) { m_history = history; }

int SimpleCalculator::Add(int a, int b) {
  int result = a + b;
  LogOperation(a, "+", b, result);
  return result;
}

int SimpleCalculator::Subtract(int a, int b) {
  int result = a - b;
  LogOperation(a, "-", b, result);
  return result;
}

int SimpleCalculator::Multiply(int a, int b) {
  int result = a * b;
  LogOperation(a, "*", b, result);
  return result;
}

int SimpleCalculator::Divide(int a, int b) {
  if (b == 0) {
    throw std::invalid_argument("Division by zero");
  }
  int result = a / b;
  LogOperation(a, "/", b, result);
  return result;
}

void SimpleCalculator::LogOperation(int a, const char* op, int b, int result) {
  std::ostringstream oss;
  oss << a << " " << op << " " << b << " = " << result;
  m_history.AddEntry(oss.str());
}

}  // namespace calc
