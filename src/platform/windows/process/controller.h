#ifndef ANTI_CHEAT_PLATFORM_WINDOWS_PROCESS_CONTROLLER_H
#define ANTI_CHEAT_PLATFORM_WINDOWS_PROCESS_CONTROLLER_H

#include "platform/windows/common/handle_wrapper.h"
#include "target/controller.h"

namespace platform::windows::process {
class Controller final : public target::IController {
 public:
  Controller() = delete;
  explicit Controller(std::string path);

  Controller(const Controller&) = delete;
  Controller& operator=(const Controller&) = delete;

  Controller(Controller&&) = default;
  Controller& operator=(Controller&&) = default;

  ~Controller() override = default;

  absl::Status launch() override;
  [[nodiscard]]
  absl::StatusOr<bool> is_running() const override;
  absl::Status terminate() override;

 private:
  absl::StatusOr<std::reference_wrapper<const common::WindowsHandle>> get_target_handle(
      const std::string& called_func_name) const;

  std::optional<common::WindowsHandle> handle_opt_ = std::nullopt;
  std::string path_;
};
}  // namespace platform::windows::process

#endif  // ANTI_CHEAT_PLATFORM_WINDOWS_PROCESS_CONTROLLER_H
