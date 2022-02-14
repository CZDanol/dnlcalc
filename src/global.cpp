#include "global.h"

#include "intrinsic/intrinsicrules.h"

Global global;

void Global::init() {
	loadIntrinsicRules(rules);
}
