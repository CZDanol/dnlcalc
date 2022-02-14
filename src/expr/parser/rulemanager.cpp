#include "rulemanager.h"

#include "expr/parser/rule/numberrule.h"

RuleManager::~RuleManager() {
	for(auto &rl: rules_)
		qDeleteAll(rl);
}
