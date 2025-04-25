#include "monitor_factory.h"
#include "../ruleset/signature_set.h"
#include "../monitor/process_montitor/process_scanner.h"
#include "../monitor/process_montitor/process_monitor.h"

using namespace std;

absl::StatusOr<ProcessMonitor> build_process_monitor()
{
	unique_ptr<Scanner<ProcessInfo>> scanner = make_unique<Scanner<ProcessInfo>>(ProcessScanner{});

	return ProcessMonitor(move(scanner));
}
