#include "process_monitor.h"
#include <iostream>

using namespace std;

ProcessMonitor::ProcessMonitor(unique_ptr<Scanner<ProcessInfo>> scanner)
    : scanner(move(scanner)), snapshot({}) {}

absl::Status ProcessMonitor::scan()
{
    auto scanned = this->scanner.get()->scan();
    if (!scanned.ok()) {
        return scanned.status();
    }
    this->snapshot = scanned.value();
    return absl::Status();
}

bool ProcessMonitor::check()
{
    return false;
}

absl::Status ProcessMonitor::run_once()
{
    auto result = this->scan();
    if (!result.ok()) {
        return result;
    }
    for (const auto& info : this->snapshot) {
        if (!info.name.has_value()) continue;
        wcout << info.name.value() << endl;
    }
    return absl::Status();
}
