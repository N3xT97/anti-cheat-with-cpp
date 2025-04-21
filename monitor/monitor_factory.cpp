#include "monitor_factory.h"
#include "../ruleset/signature_set.h"
#include "../signatures/process_signature.h"
#include <string>
#include <iostream>

using namespace std;

void build_process_blastlist()
{
	SignatureSet<ProcessSignature> process_blacklist;
	process_blacklist.set_from_json("assets/process_blacklist.json");
	for (const auto& item : process_blacklist.signatures) {
		cout << item.name.value_or("None") << endl;
	}
}
