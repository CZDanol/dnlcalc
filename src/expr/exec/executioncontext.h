#pragma once

#include "expr/exec/value.h"
#include "expr/parser/sourceref.h"

class ExecutionContext {

public:
	[[noreturn]] void error(const QString &msg);

public:
	Value functionCall(Identifier func, const QList<Value> &args);

public:
	SourceRef sourceRef;

};

