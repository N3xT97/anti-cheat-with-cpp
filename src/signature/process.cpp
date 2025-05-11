#include "process.h"

#include <algorithm>

namespace signature {
void Process::normalize() {
  if (this->name.has_value()) {
    std::ranges::transform(*this->name, this->name->begin(), std::tolower);
  }
}

SignData Process::extract() const {
  SignData data = {
    std::make_pair("name", this->name),
  };
  return data;
}
}  // namespace signature
