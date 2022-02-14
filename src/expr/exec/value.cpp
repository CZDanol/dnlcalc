#include "value.h"

#include "expr/unit/unit.h"
#include "global.h"

double Value::asNumber() const {
	switch(type) {

		case Type::number:
			return numberValue;

		default:
			throw;

	}
}

QString Value::displayString(ExecutionContext &ctx) const {
	switch(type) {

		case Type::number: {
			if(const Unit *u = global.units.matchUnits(unit).value(0))
				return QStringLiteral("%1 %2").arg(u->valueTransformer(ctx, numberValue), u->standardForm);

			return QLocale().toString(numberValue);
		}

		default:
			return QStringLiteral("##CANNOT FORMAT##");

	}
}

QString Value::matchString() const {
	switch(type) {

		case Type::number:
			return QStringLiteral("num(%1)").arg(QLocale().toString(numberValue));

		default:
			return QStringLiteral("###");

	}
}
