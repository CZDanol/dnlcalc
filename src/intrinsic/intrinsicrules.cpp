#include "intrinsicrules.h"

#include "expr/parser/rulemanager.h"
#include "expr/exec/executioncontext.h"

#include "expr/parser/rule/numberrule.h"
#include "expr/parser/rule/repeatrule.h"
#include "expr/parser/rule/regexrule.h"
#include "expr/parser/rule/stringrule.h"
#include "expr/parser/rule/recursionrule.h"

void loadIntrinsicRules(RuleManager &mgr) {
	using namespace Rules;
	using C = ExecutionContext;

	// Math rules
	{
		// a + b
		mgr.addExpression<+[](C &ctx, const Expression &a, const Repeat<String<"+"_S>, Expression> &bs) {
			Value result = a(ctx);
			for(const auto &b: bs.recs)
				result = ctx.functionCall("add"_ID, {result, std::get<1>(b)(ctx)});

			return result;
		}>();

		/*	// a - b
			mgr.addExpression<+[](C &ctx, const Expression &a, const Repeat<String<"-"_S>, Expression> &bs) {
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
			mgr.addExpression<+[](C &ctx, const Expression &a, const Repeat<String<"*"_S>, Expression> &bs) {
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
			mgr.addExpression<+[](C &ctx, const Expression &a, const Repeat<String<"/"_S>, Expression> &bs) {
				Value result = a(ctx);
				for(const auto &b: bs.recs) {
					result = Value{
						.type = Value::Type::number,
						.numberValue = result.asNumber() / std::get<1>(b)(ctx).asNumber(),
					};
				}
				return result;
			}>();*/

		// ( e )
		mgr.addExpression<+[](C &ctx, const String<"("_S> &, const Recursion<Expression> &e, const String<")"_S> &) {
			return e.r(ctx);
		}>();

		// number expression
		mgr.addExpression<+[](C &, const Number &n) {
			return Value{
				.type = Value::Type::number,
				.numberValue = n.v,
			};
		}>();
	}
}
