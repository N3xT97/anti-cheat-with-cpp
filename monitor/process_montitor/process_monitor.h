#pragma once

#include "../../monitor/monitor_interface.h"
#include "../../signatures/process_signature.h"
#include "../../monitor/process_montitor/process_info.h"

class ProcessMonitor : public Monitor {
	std::unique_ptr<Scanner<ProcessInfo>> scanner;
	std::unique_ptr<Matcher<ProcessSignature, ProcessInfo>> matcher;
	std::vector<ProcessInfo> snapshot;

public:
	ProcessMonitor(std::unique_ptr<Scanner<ProcessInfo>> scanner, std::unique_ptr<Matcher<ProcessSignature, ProcessInfo>>);
	absl::Status scan() override;
	bool check() override;
	absl::StatusOr<bool> run_once() override;
};