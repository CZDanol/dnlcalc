#pragma once

#include "expr/exec/value.h"
#include "expr/function/func/intrinsicfunction.h"
#include "util/stringutils.h"

class FunctionManager {
Q_DECLARE_TR_FUNCTIONS(FunctionManager);

public:
	~FunctionManager();

public:
	Value functionCall(ExecutionContext &ctx, Identifier func, const QList<Value> &args);

public:
	template<StaticString name, auto f>
	void addFunction() {
		const auto helper = [this]<typename... Args > (Value (*)(ExecutionContext &, Args...)) {
			functions_[Identifier::fromString(name.toString())] += new IntrinsicFunction<f, Args...>();
		};
		helper(f);
	}

public:
	// List of overloads
	QHash<Identifier, QList<Function *>> functions_;

};

