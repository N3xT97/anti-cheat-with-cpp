#pragma once

#include "interface.h"
#include <absl/status/statusor.h>
#include <absl/status/status.h>

class IProcessLauncher {
public:
	virtual absl::StatusOr<std::unique_ptr<IProcessController>> launch(const std::filesystem::path& path) = 0;
};

class IProcessController {
public:
	virtual absl::StatusOr<bool> is_alive() = 0;
	virtual absl::Status kill() = 0;
};