#pragma once

#include <filesystem>
#include "interface.h"

class RuntimeManager {
	std::filesystem::path target_path;
	std::unique_ptr<IProcessLauncher> launcher;
	std::unique_ptr<IProcessController> controller;
public:
	RuntimeManager(std::unique_ptr<IProcessLauncher>& launcher, std::string &target_path);
	absl::Status launch();
};