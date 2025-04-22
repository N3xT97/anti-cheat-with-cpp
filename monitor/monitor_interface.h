#include <absl/status/status.h>
#include <absl/status/statusor.h>
#include <optional>
#include <vector>

class Monitor {
	virtual ~Monitor() = default;
	virtual absl::Status scan() = 0;
	virtual bool check() = 0;
	virtual absl::Status run_once() = 0;
};

template<typename T>
class Scanner {
	virtual ~Scanner() = default;
	virtual absl::StatusOr<std::vector<T>> scan() = 0;
};

template<typename T, typename U>
class Matcher {
	virtual ~Matcher() = default;
	virtual T convert(const U& item) = 0;
	virtual bool is_match(const T& signature, const U& item) = 0;
	virtual std::optional<std::vector<std::pair<T, U>>> match_all() = 0;
};