#include "process_scanner.h"
#include "../../commons/windows_common.h"
#include <string>
#include <memory>

using namespace std;

WindowsHandle create_process_snapshot() {
	HANDLE snapshot_handle = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	WindowsHandle h(snapshot_handle);
	return h;
}

absl::StatusOr<std::vector<ProcessInfo>> ProcessScanner::scan()
{
	WindowsHandle snapshot_handle = create_process_snapshot();
	if (!snapshot_handle.is_valid()) {
		string msg = absl::StrFormat("Error: %s", "create_process_snapshot");
		return absl::UnknownError(msg);
	}

	vector<ProcessInfo> scanned_list;

	PROCESSENTRY32W pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32W);
	BOOL result = Process32FirstW(snapshot_handle.get(), &pe32);
	while (result) {
		scanned_list.push_back(ProcessScanner::convert(pe32));
		result = Process32NextW(snapshot_handle.get(), &pe32);
	}

	return scanned_list;
}

ProcessInfo ProcessScanner::convert(const PROCESSENTRY32W& pe32)
{
	ProcessInfo info = { pe32.th32ProcessID, pe32.szExeFile };
	return info;
}

