#pragma once

#include "expressionrule.h"
#include "expr/exec/executioncontext.h"
#include "util/valueguard.h"

namespace Rules {

	template<auto func, typename... Elements>
	class CompositeExpression final : public Expression {

	public:
		static inline const QString description = QStringLiteral("CE( %1 )").arg(QStringList{Elements::description...}.join(", "));

	public:
		static RuleSP parse(Parser &p) {
			using F = RuleSP (*)(Parser &);
			static const F parseFuncs[] = {+[](Parser &p) {
				auto r = Elements::parse(p);
				const auto &d = Elements::description;
				assert(r);
				return r;
			}...};

			QList<RuleSP> elements;
			for(const auto &parsef: parseFuncs) {
				auto r = parsef(p);
				if(r->isErrorRule())
					return r;

				p.skipWhitespace();
				elements += r;
			}

			auto r = std::make_shared<CompositeExpression>();
			r->elements.swap(elements);
			return r;
		}

		virtual Value exec(ExecutionContext &ctx) const override {
			ValueGuard _srg(ctx.sourceRef, sourceRef);
			qsizetype i = 0;
			return std::apply(func, std::tuple<ExecutionContext &, const Elements &...>{ctx, static_cast<const Elements & > (*elements.at(i++))...});
		}

	public:
		QList<RuleSP> elements;

	};

}
