#include "manager.h"

#include <spdlog/spdlog.h>

namespace target {
Manager::Manager(std::unique_ptr<IController> controller)
    : controller_(std::move(controller)) {
  spdlog::trace("target::Manager::Manager() called");
}

absl::Status Manager::launch() {
  spdlog::trace("target::Manager::launch() called");
  return this->controller_->launch();
}

absl::StatusOr<bool> Manager::is_running() const {
  spdlog::trace("target::Manager::is_running() called");
  return this->controller_->is_running();
}

absl::Status Manager::terminate() {
  spdlog::trace("target::Manager::terminate() called");
  return this->controller_->terminate();
}

}  // namespace target