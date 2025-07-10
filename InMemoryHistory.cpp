// (C) PROTEI protei.com

#include "InMemoryHistory.h"

namespace calc {

void InMemoryHistory::AddEntry(const std::string& operation) {
  m_operations.push_back(operation);
}

std::vector<std::string> InMemoryHistory::GetLastOperations(
    size_t count) const {
  auto start = m_operations.end() - std::min(count, m_operations.size());
  return {start, m_operations.end()};
}

}  // namespace calc