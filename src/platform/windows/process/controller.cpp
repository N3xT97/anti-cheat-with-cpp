#include "controller.h"

#include <Windows.h>
#include <spdlog/spdlog.h>

#include "common/status_macros.h"
#include "platform/windows/common/handle_wrapper.h"

namespace platform::windows::process {
Controller::Controller(std::string path) : path_(std::move(path)) {
  spdlog::trace("platform::windows::process::Controller::Controller() called");
}

absl::Status Controller::launch() {
  spdlog::trace("platform::windows::process::Controller::launch() called");
  std::wstring cmdline = std::wstring(this->path_.begin(), this->path_.end());
  cmdline.push_back('\0');
  STARTUPINFOW startup_info = {sizeof(startup_info)};
  PROCESS_INFORMATION process_info;
  BOOL result =
      ::CreateProcessW(cmdline.c_str(), nullptr, nullptr, nullptr, false, 0,
                       nullptr, nullptr, &startup_info, &process_info);
  if (!result) {
    const DWORD err_code = ::GetLastError();
    const std::string err_msg = absl::StrFormat(
        "%s failed: CreateProcess(%s) failed with error code %lu",
        "platform::windows::process::Controller::launch()", this->path_.c_str(),
        err_code);
    return absl::InternalError(err_msg);
  }
  ::CloseHandle(process_info.hThread);

  if (process_info.hProcess == nullptr ||
      process_info.hProcess == INVALID_HANDLE_VALUE) {
    const std::string err_msg =
        absl::StrFormat("%s failed: Invalid process handle from CreateProcess",
                        "platform::windows::process::Controller::launch()");
    return absl::InternalError(err_msg);
  }
  this->handle_opt_.emplace(common::WindowsHandle(process_info.hProcess));
  return absl::OkStatus();
}

absl::StatusOr<bool> Controller::is_running() const {
  spdlog::trace("platform::windows::process::Controller::is_running() called");
  ASSIGN_OR_RETURN(const auto& handle,
                   get_target_handle(
                       "platform::windows::process::Controller::is_running()"));
  HANDLE handle_raw = handle.get().get();
  const DWORD result = ::WaitForSingleObject(handle_raw, 0);
  switch (result) {
    case WAIT_TIMEOUT:
      return true;
    case WAIT_OBJECT_0:
      return false;
    case WAIT_FAILED: {
      const DWORD err_code = ::GetLastError();
      const std::string failed_err_msg = absl::StrFormat(
          "%s failed: WaitForSingleObject() failed with error code %lu",
          "platform::windows::process::Controller::is_running()", err_code);
      return absl::InternalError(failed_err_msg);
    }
    default: {
      const std::string unexpected_err_msg = absl::StrFormat(
          "%s failed: Unexpected result from WaitForSingleObject",
          "platform::windows::process::Controller::is_running()");
      return absl::InternalError(unexpected_err_msg);
    }
  }
}

absl::Status Controller::terminate() {
  spdlog::trace("platform::windows::process::Controller::terminate() called");
  ASSIGN_OR_RETURN(const bool is_running, this->is_running());
  if (!is_running) {
    spdlog::info(
        "platform::windows::process::Controller::terminate() skipped: Target "
        "already terminated");
    return absl::OkStatus();
  }
  ASSIGN_OR_RETURN(
      auto handle_ref,
      get_target_handle("platform::windows::process::Controller::terminate()"));
  HANDLE handle_raw = handle_ref.get().get();
  BOOL result = TerminateProcess(handle_raw, 0);
  if (!result) {
    const DWORD err_code = ::GetLastError();
    const std::string err_msg = absl::StrFormat(
        "%s failed: TerminateProcess() failed with error code %lu",
        "platform::windows::process::Controller::terminate()", err_code);
    return absl::InternalError(err_msg);
  }
  return absl::OkStatus();
}

absl::StatusOr<std::reference_wrapper<const common::WindowsHandle>>
Controller::get_target_handle(const std::string& called_func_name) const {
  spdlog::trace(
      "platform::windows::process::Controller::get_target_handle() called");
  if (handle_opt_ == std::nullopt) {
    const std::string err_msg =
        absl::StrFormat("%s failed: Invalid process handle", called_func_name);
    return absl::FailedPreconditionError(err_msg);
  }
  return std::cref(handle_opt_.value());
}
}  // namespace platform::windows::process