#include "store.h"

#include "spdlog/spdlog.h"

namespace signature {
template <SignatureLike T>
void Store<T>::add(T& sign) {
  spdlog::trace("signature::process::Store<T>::add() called");
  sign.normalize();
  size_t index = this->signs.size();
  for (const std::pair<std::string, std::optional<std::string>>& data : sign.extract()) {
    if (!data.second.has_value()) continue;
    this->index_map[data.first][data.second.value()].push_back(index);
  }
  this->signs.emplace_back(sign);
}
}  // namespace signature