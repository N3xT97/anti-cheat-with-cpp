#pragma once

#include <../../monitor/monitor_interface.h>
#include <../../monitor/process_montitor/process_info.h>

class ProcessMonitor : public Monitor {
	std::unique_ptr<Scanner<ProcessInfo>> scanner;
	std::vector<ProcessInfo> snapshot;

public:
	ProcessMonitor(std::unique_ptr<Scanner<ProcessInfo>> scanner);
	absl::Status scan() override;
	bool check() override;
	absl::Status run_once() override;
};