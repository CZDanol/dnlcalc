#include "global.h"

#include "expr/rules.h"

Global global;

void Global::init() {
	loadRules(rules);
}
