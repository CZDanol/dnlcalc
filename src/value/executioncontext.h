#pragma once

#include "value/value.h"

class ExecutionContext {

public:
	Value functionCall(Identifier func, const QList<Value> &args);

};

