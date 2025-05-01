#include "controller.h"

#include <Windows.h>
#include <spdlog/spdlog.h>

namespace platform::windows::process {
Controller::Controller(std::string path) : path_(std::move(path)) {
  spdlog::trace("platform::windows::process::Controller::Controller");
  // todo
}

absl::Status Controller::launch() {
  spdlog::trace("platform::windows::process::Controller::launch");

  const std::wstring target_path_w =
      std::wstring(this->path_.begin(), this->path_.end());
  STARTUPINFOW startup_info = {sizeof(startup_info)};
  PROCESS_INFORMATION process_info;
  ::CreateProcessW(target_path_w.c_str(), nullptr, nullptr, nullptr, false, 0,
                 nullptr, nullptr, &startup_info, &process_info);
  ::CloseHandle(process_info.hThread);
  return absl::OkStatus();
}

absl::StatusOr<bool> Controller::is_running() const {
  spdlog::trace("platform::windows::process::Controller::is_running");
  // todo
  return true;
}

absl::Status Controller::terminate() {
  spdlog::trace("platform::windows::process::Controller::terminate");
  // todo
  return absl::OkStatus();
}
}  // namespace platform::windows::process