#pragma once

#include "parser/rulemanager.h"
#include "value/functionmanager.h"

class Global {

public:
	void init();

public:
	RuleManager rules;
	FunctionManager functions;

};

extern Global global;

