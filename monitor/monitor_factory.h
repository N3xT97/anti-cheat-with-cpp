#pragma once

#include <absl/status/status.h>
#include "../monitor/process_montitor/process_monitor.h"

absl::StatusOr<ProcessMonitor> build_process_monitor();