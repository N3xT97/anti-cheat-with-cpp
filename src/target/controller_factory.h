#ifndef ANTI_CHEAT_TARGET_CONTROLLER_FACTORY_H
#define ANTI_CHEAT_TARGET_CONTROLLER_FACTORY_H

#include "target/controller.h"

namespace target {
enum class ControllerType {
  kWindows,
};

class ControllerFactory final {
 public:
  ControllerFactory() = delete;

  ControllerFactory(const ControllerFactory&) = delete;
  ControllerFactory& operator=(const ControllerFactory&) = delete;

  ControllerFactory(ControllerFactory&&) = delete;
  ControllerFactory& operator=(ControllerFactory&&) = delete;

  ~ControllerFactory() = delete;

  [[nodiscard]]
  static absl::StatusOr<std::unique_ptr<IController>> Create(
      ControllerType type, const std::string& path);
};
}  // namespace target

#endif  // ANTI_CHEAT_TARGET_CONTROLLER_FACTORY_H
