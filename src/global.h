#pragma once

#include "expr/rulemanager.h"

class Global {

public:
	void init();

public:
	RuleManager rules;

};

extern Global global;

