#include "global.h"

#include "intrinsic/intrinsicunits.h"
#include "intrinsic/intrinsicrules.h"
#include "intrinsic/intrinsicfunctions.h"

Global global;

void Global::init() {
	dataDir = QDir(QDir().absolutePath() + "/../");

	IntrinsicUnits::setup(units);
	loadIntrinsicRules(rules);
	loadIntrinsicFunctions(functions);

	units.update();
}
