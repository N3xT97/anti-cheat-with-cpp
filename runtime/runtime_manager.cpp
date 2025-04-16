#include "runtime_manager.h"

using namespace std;

RuntimeManager::RuntimeManager(unique_ptr<IProcessLauncher> launcher, string& target_path) 
	: launcher(move(launcher)), target_path(target_path), controller(nullptr) {}

absl::Status RuntimeManager::launch()
{
	auto result = this->launcher->launch(this->target_path);
	if (!result.ok()) {
		return result.status();
	}
	this->controller = move(result.value());
	return absl::OkStatus();
}

absl::Status RuntimeManager::kill()
{
	auto result = this->controller->kill();
	if (!result.ok()) {
		return result;
	}
	return absl::OkStatus();
}


