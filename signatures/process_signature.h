#pragma once

#include <string>
#include <nlohmann/json.hpp>
#include <optional>
#include "signature_interface.h"

class ProcessSignature : public Signature {
public:
	std::optional<std::string> name;
	
	std::unique_ptr<Signature> normalize() const override;
	std::vector<std::tuple<std::string, std::optional<std::string>>> field_values() override;
	void normalize_self();
};