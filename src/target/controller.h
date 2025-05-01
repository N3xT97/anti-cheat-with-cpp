#ifndef ANTI_CHEAT_TARGET_CONTROLLER_H
#define ANTI_CHEAT_TARGET_CONTROLLER_H

#include <absl/status/status.h>
#include <absl/status/statusor.h>

namespace target {
class IController {
 public:
  IController() = default;

  IController(const IController &) = delete;
  IController &operator=(const IController &) = delete;

  IController(IController &&) = default;
  IController &operator=(IController &&) = default;

  virtual ~IController() = default;

  virtual absl::Status launch() = 0;
  [[nodiscard]]
  virtual absl::StatusOr<bool> is_running() const = 0;
  virtual absl::Status terminate() = 0;
};
}  // namespace target

#endif  // ANTI_CHEAT_TARGET_CONTROLLER_H