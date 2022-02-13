#pragma once

#include "rule.h"
#include "expr/value.h"

namespace Rules {
	class Expression : public Rule {

	public:
		static inline const QString identifier = "Expression";

	public:
		virtual Value exec() const = 0;

	};
}