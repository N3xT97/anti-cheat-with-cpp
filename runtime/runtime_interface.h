#pragma once

#include "runtime_interface.h"
#include <absl/status/statusor.h>
#include <absl/status/status.h>
#include <filesystem>

class IProcessController {
public:
	virtual absl::StatusOr<bool> is_alive() = 0;
	virtual absl::Status kill() = 0;
	virtual ~IProcessController() = default;
};

class IProcessLauncher {
public:
	virtual absl::StatusOr<std::unique_ptr<IProcessController>> launch(const std::filesystem::path& path) = 0;
	virtual ~IProcessLauncher() = default;
};

