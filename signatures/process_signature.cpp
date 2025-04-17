#include "process_signature.h"
#include <algorithm>


using namespace std;

unique_ptr<Signature> ProcessSignature::normalize() const
{
    unique_ptr<ProcessSignature> process_sign = make_unique<ProcessSignature>(*this);
    process_sign->normalize();
	return process_sign;
}

vector<tuple<string, optional<string>>> ProcessSignature::field_values()
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
