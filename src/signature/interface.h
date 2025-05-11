#ifndef ANTI_CHEAT_SIGNATURE_INTERFACE_H
#define ANTI_CHEAT_SIGNATURE_INTERFACE_H

#include <optional>
#include <string>
#include <vector>

namespace signature {
using SignData =
    std::vector<std::pair<std::string, std::optional<std::string>>>;

class ISignature {
 public:
  virtual void normalize() = 0;
  virtual SignData extract() const = 0;
  virtual ~ISignature() = default;
};

template <typename T>
concept SignatureLike = requires(T t) {
  { t.normalize() } -> std::same_as<void>;
  { t.extract() } -> std::same_as<SignData>;
};
}  // namespace signature

#endif  // ANTI_CHEAT_SIGNATURE_INTERFACE_H
