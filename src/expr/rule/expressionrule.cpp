#include "expressionrule.h"

#include "expr/parser.h"

RuleSP Rules::Expression::parse(Parser &p) {
	return p.parse(identifier);
}
