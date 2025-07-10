// (C) PROTEI protei.com

#pragma once

#include <string>
#include <vector>

namespace calc {

class IHistory {
 public:
  virtual ~IHistory() = default;

  virtual void AddEntry(const std::string& operation) = 0;
  virtual std::vector<std::string> GetLastOperations(size_t count) const = 0;
};

}  // namespace calc
