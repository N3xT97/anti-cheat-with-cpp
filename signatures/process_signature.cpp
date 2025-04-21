#include "process_signature.h"
#include <algorithm>
#include <optional>

using namespace std;

unique_ptr<Signature> ProcessSignature::normalize() const
{
    unique_ptr<ProcessSignature> process_sig = make_unique<ProcessSignature>(*this);
    process_sig->normalize_self();
	return process_sig;
}

vector<tuple<string, optional<string>>> ProcessSignature::field_values() const
{
    vector<tuple<string, optional<string>>> field_values = {
        {"name", this->name}
    };
    return field_values;
}

void ProcessSignature::normalize_self()
{
    if (this->name.has_value()) {
        std::string& n = this->name.value();
        std::transform(n.begin(), n.end(), n.begin(), [](unsigned char c) {
            return std::tolower(c);
        });
    }
}

unique_ptr<Signature> ProcessSignature::from_json(const nlohmann::json& j) {
    auto sig = std::make_unique<ProcessSignature>();
    if (j.contains("name") && j["name"].is_string()) {
        sig->name = j["name"].get<std::string>();
    }
    else {
        sig->name = std::nullopt;
    }
    return sig;
}
