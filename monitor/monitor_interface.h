#include <absl/status/status.h>
#include <absl/status/statusor.h>
#include <optional>
#include <vector>

class Monitor {
public:
	virtual ~Monitor() = default;
	virtual absl::Status scan() = 0;
	virtual bool check() = 0;
	virtual absl::StatusOr<bool> run_once() = 0;
};

template<typename T>
class Scanner {
public:
	virtual ~Scanner() = default;
	virtual absl::StatusOr<std::vector<T>> scan() = 0;
};

template<typename T, typename U>
class Matcher {
public:
	virtual ~Matcher() = default;
	virtual T convert(const U& item) = 0;
	virtual bool is_match(const T& signature, const U& item) = 0;
	virtual std::optional<std::vector<std::pair<T, U>>> match_all(std::vector<U>& items) = 0;
};