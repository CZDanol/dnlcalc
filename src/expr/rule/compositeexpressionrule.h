#pragma once

#include "expressionrule.h"

namespace Rules {

	template<auto func, typename... Elements>
	class CompositeExpression final : public Expression {

	public:
		static inline const QString description = QStringLiteral("CompositeExpression( %1 )").arg(QStringList{Elements::description...}.join(", "));

	public:
		static RuleSP parse(Parser &p) {
			static const auto els = QList{Elements::identifier...};

			QList<RuleSP> elements;
			for(Identifier ruleId: els) {
				auto r = p.parse(ruleId);
				if(r->isErrorRule())
					return r;

				p.skipWhitespace();
				elements += r;
			}

			auto r = std::make_shared<CompositeExpression>();
			r->elements.swap(elements);
			return r;
		}

		virtual Value exec() const override {
			qsizetype i = 0;
			return std::apply(func, std::tuple<const Elements &...>{*static_cast<const Elements * > (elements.at(i++).get())...});
		}

	public:
		QList<RuleSP> elements;

	};

}