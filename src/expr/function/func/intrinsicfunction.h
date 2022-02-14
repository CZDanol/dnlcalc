#pragma once

#include "function.h"
#include "expr/exec/executioncontext.h"

template<auto func, typename... Args>
class IntrinsicFunction final : public Function {
	Q_DECLARE_TR_FUNCTIONS(IntrinsicFunction)

public:
	virtual Value call(ExecutionContext &ctx, const QList <Value> &args) const override {
		using Tuple = std::tuple<ExecutionContext &, Args...>;
		qsizetype i = 0;
		Tuple argst = Tuple{ctx, Args::match(ctx, args, i)...};

		return std::apply(func, argst);
	};

};