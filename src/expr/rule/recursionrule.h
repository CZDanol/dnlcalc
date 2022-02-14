#pragma once

#include "rule.h"

namespace Rules {

	template<typename T>
	class Recursion : public Rule {

	public:
		static inline const QString description = QStringLiteral("!%1").arg(T::description);

	public:
		static RuleSP parse(Parser &p) {
			p.resetRecursion(T::identifier);
			RuleSP r = T::parse(p);
			if(r->isErrorRule())
				return r;

			return std::make_shared<Recursion>(std::move(r));
		}

	public:
		const T &r;
		RuleSP rule;

	public:
		Recursion(RuleSP &&r) : r(dynamic_cast<const T &>(*r)), rule(r) {}

	};

}