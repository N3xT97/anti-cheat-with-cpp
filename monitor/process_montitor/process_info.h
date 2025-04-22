#pragma once

#include <optional>
#include <Windows.h>
#include <string>

class ProcessInfo {
public:
	std::optional<DWORD> pid;
	std::optional<std::wstring> name;
};