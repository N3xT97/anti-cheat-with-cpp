#pragma once

#include "../../monitor/monitor_interface.h"
#include "../../signatures/process_signature.h"
#include "../../ruleset/signature_set.h"
#include "process_info.h"
#include <optional>
#include <vector>

class ProcessMatcher : public Matcher<ProcessSignature, ProcessInfo> {
	SignatureSet<ProcessSignature> blacklist;
public:
	ProcessSignature convert(const ProcessInfo& item) override;
	bool is_match(const ProcessSignature& signature, const ProcessInfo& item) override;
	std::optional<std::vector<std::pair<ProcessSignature, ProcessInfo>>> match_all(std::vector<ProcessInfo>& items) override;
};