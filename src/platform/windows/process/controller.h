#ifndef ANTI_CHEAT_PLATFROM_WINDOWS_PROCESS_CONTROLLER_H
#define ANTI_CHEAT_PLATFROM_WINDOWS_PROCESS_CONTROLLER_H

#include <Windows.h>

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
  std::string path_;
  struct HandleCloser {
    void operator()(HANDLE h) const { ::CloseHandle(h); }
  };
  std::optional<common::HandleWrapper<HANDLE, HandleCloser>> handle_opt_ =
      std::nullopt;
};
}  // namespace platform::windows::process

#endif  // ANTI_CHEAT_PLATFROM_WINDOWS_PROCESS_CONTROLLER_H
