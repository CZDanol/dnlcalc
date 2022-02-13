#include "rules.h"

#include "rulemanager.h"

#include "rule/numberrule.h"
#include "rule/regexrule.h"

void loadRules(RuleManager &r) {
	using namespace Rules;

	r.addRule<Number>();

	// Math rules
	{
		// a + b
		r.addExpression<+[](const Expression &a, const Regex<"+"_S> &, const Expression &b) {
			return Value{
				.type = Value::Type::number,
				.numberValue = a.exec().asNumber() + b.exec().asNumber(),
			};
		}>();

		// ( e )
		r.addExpression<+[](const Regex<"\\("_S> &, const Expression &e, const Regex<"\\)"_S> &) {
			return e.exec();
		}>();

		// number expression
		r.addExpression<+[](const Number &n) {
			return Value{
				.type = Value::Type::number,
				.numberValue = n.v,
			};
		}>();
	}
}
