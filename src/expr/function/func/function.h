#pragma once

#include "expr/exec/value.h"

class Function {

public:
	virtual ~Function() = default;

public:
	/// Calls the function or returns error if mismatch or anything
	virtual Value call(ExecutionContext &ctx, const QList<Value> &args) const = 0;

};