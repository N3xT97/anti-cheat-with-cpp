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
	absl::Status result = target.launch();
	if (!result.ok()) return result;

	auto process_monitor = build_process_monitor();
	if (!process_monitor.ok()) return process_monitor.status();

	result = process_monitor.value().run_once();
	if (!result.ok()) return result;

	result = target.kill();
	if (!result.ok()) {
		return result;
	}
	return absl::OkStatus();
}
