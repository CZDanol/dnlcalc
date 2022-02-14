#include "intrinsicrules.h"

#include "parser/rulemanager.h"
#include "value/executioncontext.h"

#include "parser/rule/numberrule.h"
#include "parser/rule/repeatrule.h"
#include "parser/rule/regexrule.h"
#include "parser/rule/stringrule.h"
#include "parser/rule/recursionrule.h"

void loadIntrinsicRules(RuleManager &r) {
	using namespace Rules;

	// Math rules
	{
		// a + b
		r.addExpression<+[](ExecutionContext &ctx, const Expression &a, const Repeat<String<"+"_S>, Expression> &bs) {
			Value result = a(ctx);
			for(const auto &b: bs.recs) {
				result = Value{
					.type = Value::Type::number,
					.numberValue = result.asNumber() + std::get<1>(b)(ctx).asNumber(),
				};
			}
			return result;
		}>();

		// a - b
		r.addExpression<+[](ExecutionContext &ctx, const Expression &a, const Repeat<String<"-"_S>, Expression> &bs) {
			Value result = a(ctx);
			for(const auto &b: bs.recs) {
				result = Value{
					.type = Value::Type::number,
					.numberValue = result.asNumber() - std::get<1>(b)(ctx).asNumber(),
				};
			}
			return result;
		}>();

		// a * b
		r.addExpression<+[](ExecutionContext &ctx, const Expression &a, const Repeat<String<"*"_S>, Expression> &bs) {
			Value result = a(ctx);
			for(const auto &b: bs.recs) {
				result = Value{
					.type = Value::Type::number,
					.numberValue = result.asNumber() * std::get<1>(b)(ctx).asNumber(),
				};
			}
			return result;
		}>();

		// a / b
		r.addExpression<+[](ExecutionContext &ctx, const Expression &a, const Repeat<String<"/"_S>, Expression> &bs) {
			Value result = a(ctx);
			for(const auto &b: bs.recs) {
				result = Value{
					.type = Value::Type::number,
					.numberValue = result.asNumber() / std::get<1>(b)(ctx).asNumber(),
				};
			}
			return result;
		}>();

		// ( e )
		r.addExpression<+[](ExecutionContext &ctx, const String<"("_S> &, const Recursion<Expression> &e, const String<")"_S> &) {
			return e.r(ctx);
		}>();

		// number expression
		r.addExpression<+[](ExecutionContext &, const Number &n) {
			return Value{
				.type = Value::Type::number,
				.numberValue = n.v,
			};
		}>();
	}
}
