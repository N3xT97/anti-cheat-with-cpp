#include "launcher.h"

using namespace std;

WindowsProcessController::WindowsProcessController(WindowsHandle handle)
	: handle(move(handle)) {
}

absl::StatusOr<bool> WindowsProcessController::is_alive()
{
	if (!this->handle.is_valid()) {
		string msg = absl::StrFormat("Error: %s", "INVALID_HANDLE_VALUE");
		return absl::UnknownError(msg);
	}
	DWORD exit_code = 0;
	BOOL result = GetExitCodeProcess(this->handle.get(), &exit_code);
	if (!result) {
		DWORD error = GetLastError();
		string msg = absl::StrFormat("Error(%d): %s", error, "GetExitCodeProcess");
		return absl::UnknownError(msg);
	}
	bool state = (exit_code == STILL_ACTIVE);
	return absl::StatusOr<bool>(state);
}

absl::Status WindowsProcessController::kill()
{
	absl::StatusOr<bool> is_alive_or = this->is_alive();
	if (!is_alive_or.ok()) {
		return is_alive_or.status();
	}
	if (!is_alive_or.value()) {
		return absl::OkStatus();
	}

	BOOL result = TerminateProcess(this->handle.get(), 1);
	if (!result) {
		DWORD error = GetLastError();
		string msg = absl::StrFormat("Error(%d): %s", error, "TerminateProcess");
		return absl::UnknownError(msg);
	}

	return absl::OkStatus();
}

absl::StatusOr<std::unique_ptr<IProcessController>> WindowsProcessLauncher::launch(const std::filesystem::path& path)
{
	if (!filesystem::exists(path)) {
		string msg = absl::StrFormat("Error: '%s' is not existed", path.string());
		return absl::NotFoundError(msg);
	}
	wstring command = path.wstring();
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi = {};
	BOOL result = CreateProcessW(
		command.c_str(),
		nullptr,
		nullptr,
		nullptr,
		FALSE,
		0,
		nullptr,
		nullptr,
		&si,
		&pi
	);
	if (!result) {
		DWORD error = GetLastError();
		string msg = absl::StrFormat("Error(%d): %s(%s)", error, "CreateProcessW", path.string());
		return absl::UnknownError(msg);
	}
	result = CloseHandle(pi.hThread);
	if (!result) {
		DWORD error = GetLastError();
		string msg = absl::StrFormat("Error(%d): %s", error, "CloseHandle");
		return absl::UnknownError(msg);
	}
	unique_ptr<WindowsProcessController> process_controller = make_unique<WindowsProcessController>(WindowsProcessController(WindowsHandle(pi.hProcess)));
	return process_controller;
}
