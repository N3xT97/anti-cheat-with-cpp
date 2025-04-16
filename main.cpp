#include <absl/status/status.h>
#include <iostream>

#include "app.h"


using namespace std;

int main() {
	absl::Status result = run();
	if (!result.ok()) {
		cout << result.message() << endl;
		return 1;
	}
	return 0;
}