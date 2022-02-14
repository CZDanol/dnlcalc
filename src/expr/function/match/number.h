#pragma once

#include "valuematch.h"

namespace ArgsMatching {

	struct Number : public ArgsMatch, public Value {
		Q_DECLARE_TR_FUNCTIONS(Number)

	public:
		static inline const Identifier identifier = "Number"_ID;

	public:
		static Number match(ExecutionContext &ctx, const QList<Value> &args, qsizetype &i);
	};

}