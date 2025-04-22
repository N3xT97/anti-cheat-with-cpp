#pragma once

#include "../monitor_interface.h"
#include "process_info.h"
#include <TlHelp32.h>

class ProcessScanner : public Scanner<ProcessInfo> {
public:
	virtual absl::StatusOr<std::vector<ProcessInfo>> scan() override;
	static ProcessInfo convert(const PROCESSENTRY32W& pe32);
};