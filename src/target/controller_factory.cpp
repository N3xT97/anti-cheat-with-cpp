#include "controller_factory.h"

#include <spdlog/spdlog.h>

#if defined(_WIN32)
#include "platform/windows/process/controller.h"
#endif

namespace target {
absl::StatusOr<std::unique_ptr<IController>> ControllerFactory::Create(
    ControllerType type, const std::string& path) {
  spdlog::trace("target::ControllerFactory::Create");
  switch (type) {
    case ControllerType::kWindows:
      return absl::make_unique<platform::windows::process::Controller>(path);
    default:
      return absl::InvalidArgumentError("Unknown Controller type");
  }
}
}  // namespace target
