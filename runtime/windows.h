#pragma once
#include "interface.h"
#include "../commons/windows_common.h"

class WindowsProcessController : public IProcessController {
	WindowsHandle handle;
public:
};

class WindowsProcessLauncher : public IProcessLauncher {
};