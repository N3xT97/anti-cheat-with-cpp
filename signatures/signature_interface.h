#pragma once

#include <vector>
#include <tuple>
#include <string>
#include <optional>
#include <memory>

class Signature {
public:
	virtual std::unique_ptr<Signature> normalize() const= 0;
	virtual std::vector<std::tuple<std::string, std::optional<std::string>>> field_values() = 0;
	virtual ~Signature() = default;
};