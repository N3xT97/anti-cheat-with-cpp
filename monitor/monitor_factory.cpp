#include "monitor_factory.h"
#include "../ruleset/signature_set.h"
#include "../monitor/process_montitor/process_scanner.h"
#include "../monitor/process_montitor/process_monitor.h"
#include "../monitor/process_montitor/process_matcher.h"
#include <memory>

using namespace std;

absl::StatusOr<ProcessMonitor> build_process_monitor()
{
	SignatureSet<ProcessSignature> signature_set;
	auto blacklist_result = signature_set.set_from_json("assets/process_blacklist.json");
	if (!blacklist_result.ok()) {
		return blacklist_result;
	}
	unique_ptr<IMatcher<ProcessSignature, ProcessInfo>> matcher = make_unique<ProcessMatcher>(ProcessMatcher(signature_set));
	unique_ptr<IScanner<ProcessInfo>> scanner = make_unique<ProcessScanner>(ProcessScanner());
	return ProcessMonitor(move(scanner), move(matcher));
}
