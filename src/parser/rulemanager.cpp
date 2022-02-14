#include "rulemanager.h"

#include "rule/numberrule.h"

RuleManager::~RuleManager() {
	for(auto &rl: rules_)
		qDeleteAll(rl);
}
