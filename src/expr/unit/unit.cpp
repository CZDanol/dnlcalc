#include "unit.h"

QString Unit::defaultValueTransformer(ExecutionContext &, double v) {
	return QLocale().toString(v);
}
