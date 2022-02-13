#include "rules.h"

#include "rulemanager.h"

#include "rule/numberrule.h"
#include "rule/regexrule.h"
#include "rule/stringrule.h"

void loadRules(RuleManager &r) {
	using namespace Rules;

	r.addRule<Number>();

	// Math rules
	{
		// a + b
		r.addExpression<+[](const Expression &a, const String<"+"_S> &, const Expression &b) {
			return Value{
				.type = Value::Type::number,
				.numberValue = a.exec().asNumber() + b.exec().asNumber(),
			};
		}>();

		// ( e )
		r.addExpression<+[](const String<"("_S> &, const Expression &e, const String<")"_S> &) {
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
