#include "value.h"

double Value::asNumber() const {
	switch(type) {

		case Type::number:
			return numberValue;

		default:
			throw;

	}
}

QString Value::displayString() const {
	switch(type) {

		case Type::number:
			return QStringLiteral("%1 %2").arg(QLocale().toString(numberValue), unit);

		default:
			return QStringLiteral("##CANNOT FORMAT##");

	}
}
