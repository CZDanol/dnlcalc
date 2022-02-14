#pragma once

#include "rule.h"
#include "expr/exec/value.h"

namespace Rules {

	class Expression : public Rule {

	public:
		static inline const Identifier identifier = "Expression"_ID;
		static inline const QString description = "Expression";

	public:
		static RuleSP parse(Parser &p);

	public:
		virtual Value exec(ExecutionContext &ctx) const = 0;

		inline Value operator ()(ExecutionContext &ctx) const {
			return exec(ctx);
		}

	};

}