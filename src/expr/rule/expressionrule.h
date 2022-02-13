#pragma once

#include "rule.h"
#include "expr/value.h"

namespace Rules {

	class Expression : public Rule {

	public:
		static inline const Identifier identifier = "Expression"_ID;
		static inline const QString description = "Expression";

	public:
		virtual Value exec() const = 0;

	};

}