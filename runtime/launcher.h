#pragma once
#include <filesystem>
#include <absl/status/statusor.h>

#include "runtime_interface.h"
#include "../commons/windows_common.h"

class WindowsProcessController : public IProcessController {
	WindowsHandle handle;
public:
	explicit WindowsProcessController(WindowsHandle handle);
	absl::StatusOr<bool> is_alive() override;
	absl::Status kill() override;
};

class WindowsProcessLauncher : public IProcessLauncher {
	absl::StatusOr<std::unique_ptr<IProcessController>> launch(const std::filesystem::path& path) override;
};