#include "signature_set.h"
#include "../signatures/process_signature.h"
#include <nlohmann/json.hpp>
#include <absl/strings/str_format.h>
#include <fstream>

using namespace std;

template<typename T>
requires derived_from<T, Signature>
void SignatureSet<T>::insert(T& signature)
{
	signature.normalize();
	size_t idx = this->signatures.size();
	for (const auto& [field, value_opt]: signature.field_values()) {
		if (!value_opt.has_value()) continue;
		const std::string& value = value_opt.value();
		auto& value_map = this->field_index.try_emplace(field, FieldValueMap{}).first->second;
		auto& index_list = value_map.try_emplace(value, std::vector<size_t>{}).first->second;
		index_list.push_back(idx);
	}
	this->signatures.push_back(move(signature));
}

template<typename T>
requires derived_from<T, Signature>
absl::Status SignatureSet<T>::set_from_json(const string& path)
{
	ifstream input(path);
	if (!input.is_open()) {
		string msg = absl::StrFormat("Error: '%s' is not existed...", path);
		return absl::NotFoundError(msg);
	}

	nlohmann::json j;
	try {
		input >> j;
	}
	catch (const nlohmann::json::type_error& e) {
		string msg = absl::StrFormat("Error(json): %s", e.what());
		return absl::UnknownError(msg);
	}

	if (!j.is_array()) {
		string msg = absl::StrFormat("Error(): %s", "is_array");
		return absl::UnknownError(msg);
	}

	this->signatures.clear();
	this->field_index.clear();

	for (const auto& item : j) {
		std::unique_ptr<Signature> sig = T::from_json(item);
		ProcessSignature* typed_ptr = dynamic_cast<ProcessSignature*>(sig.get());
		this->insert(*typed_ptr);
	}
	return absl::OkStatus();
}

template<typename T>
requires derived_from<T, Signature>
optional<vector<T>> SignatureSet<T>::search_all(T& signature)
{
	vector<T> matches;
	for (const auto& [field, value_opt] : signature.field_values()) {
		if (!value_opt.has_value()) continue;
		const string& value = value_opt.value();
		auto field_map_it = this->field_index.find(field);
		if (field_map_it == this->field_index.end()) continue;
		const auto& value_map = field_map_it->second;
		auto value_map_it = value_map.find(value);
		if (value_map_it == value_map.end()) continue;
		const auto& index_list = value_map_it->second;
		for (size_t idx : index_list) {
			matches.push_back(this->signatures.at(idx));
		}
	}
	if (matches.empty()) return nullopt;
	return matches;
}


template class SignatureSet<ProcessSignature>;