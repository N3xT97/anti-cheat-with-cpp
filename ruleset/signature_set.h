#pragma once

#include "../signatures/signature_interface.h"
#include <absl/status/status.h>
#include <unordered_map>
#include <string>
#include <vector>

using FieldValueMap = std::unordered_map<std::string, std::vector<size_t>>;
using FieldIndexMap = std::unordered_map<std::string, FieldValueMap>;

template<typename T>
requires std::derived_from<T, Signature>
class SignatureSet {
public:
	std::vector<T> signatures;
	FieldIndexMap field_index;

	void insert(T& signature);
	absl::Status set_from_json(std::string& path);
	std::optional search_all(T& signature);
};