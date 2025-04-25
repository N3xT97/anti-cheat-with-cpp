#include "process_matcher.h"
#include <optional>
#include <string>

using namespace std;

ProcessSignature ProcessMatcher::convert(const ProcessInfo& item)
{
	ProcessSignature sig;
	if (item.name.has_value()) {
		sig.name = string(item.name->begin(), item.name->end());
	}
	else {
		sig.name = nullopt;
	}
	return sig;
}

bool ProcessMatcher::is_match(const ProcessSignature& signature, const ProcessInfo& item)
{
	ProcessSignature input = this->convert(item);
	if (signature.name.has_value() && input.name.has_value()) {
		if (signature.name.value() != input.name.value()) {
			return false;
		}
	}
	return true;
}

optional<vector<pair<ProcessSignature, ProcessInfo>>> ProcessMatcher::match_all(vector<ProcessInfo>& items)
{
	vector<pair<ProcessSignature, ProcessInfo>> matches;
	for (const auto& itme : items) {
		ProcessSignature sig = this->convert(itme);
		if (this->is_match(sig, itme)) {
			matches.push_back(make_pair(sig, itme));
		}
	}
	return matches.empty() ? nullopt : make_optional(matches);
}
