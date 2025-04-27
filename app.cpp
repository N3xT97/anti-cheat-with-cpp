#include <absl/status/status.h>
#include <absl/log/log.h>

#include "app.h"
#include "cui/cui_manager.h"
#include "runtime/runtime_factory.h"
#include "monitor/monitor_factory.h"

using namespace std;

absl::Status run()
{
	CuiManager cui;
	cui.print_logo();

	string target_path = "C:\\Windows\\System32\\notepad.exe";
	RuntimeManager target = build_runtime_manager(target_path);
	absl::Status launcher_result = target.launch();
	if (!launcher_result.ok()) return launcher_result;

	auto process_monitor = build_process_monitor();
	if (!process_monitor.ok()) return process_monitor.status();

	while (true)
	{
		absl::StatusOr<bool> monitor_result = process_monitor.value().run_once();
		if (!monitor_result.ok()) return monitor_result.status();
		if (monitor_result.value()) break;
	}

	launcher_result = target.kill();
	if (!launcher_result.ok()) {
		return launcher_result;
	}
	return absl::OkStatus();
}
