#include "global.h"

#include "intrinsic/intrinsicrules.h"
#include "intrinsic/intrinsicfunctions.h"

Global global;

void Global::init() {
	loadIntrinsicRules(rules);
	loadIntrinsicFunctions(functions);
}
