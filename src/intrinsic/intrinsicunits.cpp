#include "intrinsicunits.h"

#include "expr/unit/unitmanager.h"

void IntrinsicUnits::setup(UnitManager &mgr) {
	// Length
	{
		auto *q = mgr.addQuantity("length"_ID, tr("length"));

		mgr.addUnit("m", q, 1, "m");
		mgr.addUnit("cm", q, 0.01, "cm");
	}

	// Angle
	{
		auto *q = mgr.addQuantity("angle"_ID, tr("angle"));

		mgr.addUnit("°", q, 1, "°|deg");
		mgr.addUnit("rad", q, M_PI_4, "rad");
	}

	// Numeral system
	{
		auto *q = mgr.addQuantity("numSystem"_ID, tr("numeral system"));

		mgr.addUnit("DEC", q, 1, "dec|DEC");
		mgr.addUnit("HEX", q, 1, "hex|HEX", [](ExecutionContext &ctx, double v) {
			return "0x" + QString::number(static_cast<qlonglong>(v), 16).toUpper();
		});
		mgr.addUnit("OCT", q, 1, "oct|OCT", [](ExecutionContext &ctx, double v) {
			return "0" + QString::number(static_cast<qlonglong>(v), 8);
		});
	}
}
