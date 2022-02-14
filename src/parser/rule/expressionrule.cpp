#include "expressionrule.h"

#include "parser/parser.h"

RuleSP Rules::Expression::parse(Parser &p) {
	return p.parse(identifier);
}
