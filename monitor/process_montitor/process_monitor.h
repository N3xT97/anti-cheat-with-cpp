#pragma once

#include "../../monitor/monitor_interface.h"
#include "../../signatures/process_signature.h"
#include "../../monitor/process_montitor/process_info.h"

class ProcessMonitor : public IMonitor {
	std::unique_ptr<IScanner<ProcessInfo>> scanner;
	std::unique_ptr<IMatcher<ProcessSignature, ProcessInfo>> matcher;
	std::vector<ProcessInfo> snapshot;

public:
	ProcessMonitor(std::unique_ptr<IScanner<ProcessInfo>> scanner, std::unique_ptr<IMatcher<ProcessSignature, ProcessInfo>> matcher);
	absl::Status scan() override;
	bool check() override;
	absl::StatusOr<bool> run_once() override;
};