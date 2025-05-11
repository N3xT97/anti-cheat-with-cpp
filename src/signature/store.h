#ifndef ANTI_CHEAT_SIGNATURE_STORE_H
#define ANTI_CHEAT_SIGNATURE_STORE_H

#include <absl/status/status.h>

#include <string>
#include <unordered_map>
#include <vector>

#include "signature/interface.h"

namespace signature {

using ValueMap = std::unordered_map<std::string, std::vector<size_t>>;
using FieldMap = std::unordered_map<std::string, ValueMap>;

template <SignatureLike T>
class Store {
 public:
  Store() = default;

  Store(const Store &) = delete;
  Store &operator=(const Store &) = delete;
  Store(Store &&) = default;
  Store &operator=(Store &&) = default;

  ~Store() = default;

  void add(T &sign);

 private:
  std::vector<T> signs;
  FieldMap index_map;
};
}  // namespace Signature

#endif  // ANTI_CHEAT_SIGNATURE_STORE_H