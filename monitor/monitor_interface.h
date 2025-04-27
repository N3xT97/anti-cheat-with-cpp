#pragma once

#include <absl/status/status.h>
#include <absl/status/statusor.h>
#include <optional>
#include <vector>

class IMonitor {
public:
	virtual ~IMonitor() = default;
	virtual absl::Status scan() = 0;
	virtual bool check() = 0;
	virtual absl::StatusOr<bool> run_once() = 0;
};

template<typename T>
class IScanner {
public:
	virtual ~IScanner() = default;
	virtual absl::StatusOr<std::vector<T>> scan() = 0;
};

template<typename T, typename U>
class IMatcher {
public:
	virtual ~IMatcher() = default;
	virtual T convert(const U& item) = 0;
	virtual bool is_match(const T& signature, const T& item) = 0;
	virtual std::optional<std::vector<std::pair<T, U>>> match_all(std::vector<U>& items) = 0;
};