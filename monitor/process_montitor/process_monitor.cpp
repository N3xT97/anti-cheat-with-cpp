#include "process_monitor.h"
#include <iostream>

using namespace std;

ProcessMonitor::ProcessMonitor(unique_ptr<Scanner<ProcessInfo>> scanner, unique_ptr<Matcher<ProcessSignature, ProcessInfo>> matcher)
    : scanner(move(scanner)), matcher(move(matcher)), snapshot({}) { }

absl::Status ProcessMonitor::scan()
{
    auto scanned = this->scanner.get()->scan();
    if (!scanned.ok()) {
        return scanned.status();
    }
    this->snapshot = scanned.value();
    return absl::OkStatus();
}

bool ProcessMonitor::check()
{
    auto result = this->scan();
	if (!result.ok()) {
		return false;
	}
    auto matches = this->matcher.get()->match_all(this->snapshot);
	if (!matches.has_value()) {
		return false;
	}
	for (const auto& match : matches.value()) {
		cout << "Match found: " << match.first.name.value() << endl;
	}
    return false;
}

absl::StatusOr<bool> ProcessMonitor::run_once()
{
    auto scan_result = this->scan();
    if (!scan_result.ok()) {
        return scan_result;
    }
	auto check_result = this->check();
	return check_result;
}
