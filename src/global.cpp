#include "global.h"

#include "intrinsic/intrinsicunits.h"
#include "intrinsic/intrinsicrules.h"
#include "intrinsic/intrinsicfunctions.h"

Global global;

void Global::init() {
	loadIntrinsicUnits(units);
	loadIntrinsicRules(rules);
	loadIntrinsicFunctions(functions);
}
