#include "app.h"
#include "absl/status/status.h"
#include "cui/manager.h"

absl::Status run()
{
	CuiManager cui;
	cui.print_logo();
	return absl::OkStatus();
}
