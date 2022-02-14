#pragma once

#include "expr/parser/rulemanager.h"
#include "expr/function/functionmanager.h"
#include "expr/unit/unitmanager.h"

class Global {

public:
	void init();

public:
	UnitManager units;
	RuleManager rules;
	FunctionManager functions;

public:
	QDir dataDir;

};

extern Global global;

