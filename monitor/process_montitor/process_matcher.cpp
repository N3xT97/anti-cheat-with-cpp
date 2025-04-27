#include "process_matcher.h"
#include <optional>
#include <string>

using namespace std;

ProcessMatcher::ProcessMatcher(SignatureSet<ProcessSignature>& blacklist)
	: blacklist(blacklist) {}


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

bool ProcessMatcher::is_match(const ProcessSignature& signature, const ProcessSignature& input)
{
	if (signature.name.has_value()) {
		if (signature.name.value() != input.name.value()) {
			return false;
		}
	}
	return true;
}

optional<vector<pair<ProcessSignature, ProcessInfo>>> ProcessMatcher::match_all(vector<ProcessInfo>& items)
{
	vector<pair<ProcessSignature, ProcessInfo>> matches;
	for (const auto& item : items) {
		ProcessSignature item_sig = this->convert(item);
		auto searched_list = this->blacklist.search_all(item_sig);
		if (!searched_list.has_value()) continue;
		for (const auto& searched : searched_list.value()) {
			if (this->is_match(searched, item_sig)) {
				matches.push_back(make_pair(searched, item));
			}
		}
	}
	return matches.empty() ? nullopt : make_optional(matches);
}
