#pragma once

#include "expr/parser/rulemanager.h"
#include "expr/function/functionmanager.h"

class Global {

public:
	void init();

public:
	RuleManager rules;
	FunctionManager functions;

};

extern Global global;

