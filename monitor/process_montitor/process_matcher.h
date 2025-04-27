#pragma once

#include "../../monitor/monitor_interface.h"
#include "../../signatures/process_signature.h"
#include "../../ruleset/signature_set.h"
#include "process_info.h"
#include <optional>
#include <vector>

class ProcessMatcher : public IMatcher<ProcessSignature, ProcessInfo> {
	SignatureSet<ProcessSignature> blacklist;
public:
	ProcessMatcher(SignatureSet<ProcessSignature>& blacklist);
	ProcessSignature convert(const ProcessInfo& item) override;
	bool is_match(const ProcessSignature& signature, const ProcessSignature& input) override;
	std::optional<std::vector<std::pair<ProcessSignature, ProcessInfo>>> match_all(std::vector<ProcessInfo>& items) override;
};