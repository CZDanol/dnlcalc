#include "rules.h"

#include "rulemanager.h"

#include "rule/numberrule.h"

void loadRules(RuleManager &r) {
	using namespace Rules;

	r.addRule<Number>();

	// Math rules
	{
		r.addExpression<+[](const Number &n) {
			return Value{
				.type = Value::Type::number,
				.numberValue = n.v,
			};
		}>();
	}
}
