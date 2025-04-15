#include "app.h"
#include "absl/status/status.h"
#include <iostream>

using namespace std;

int main() {
	absl::Status result = run();
	if (!result.ok()) {
		cout << "Error: " << result << endl;
		return 1;
	}
	return 0;
}