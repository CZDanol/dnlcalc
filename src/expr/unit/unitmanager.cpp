#include "unitmanager.h"

#include "unit.h"
#include "quantity.h"
#include "util/iterator.h"
#include "expr/exec/executioncontext.h"

UnitManager::~UnitManager() {
	qDeleteAll(units_);
	qDeleteAll(quantities_);
}

void UnitManager::update() {
	combinedUnitsRegex_ = QRegularExpression(iterator(units_).mapx(x->regex.pattern()).join("|"));
}

Value UnitManager::convertValue(ExecutionContext &ctx, Value v, const QString &targetUnit) const {
	if(v.type != ValueType::number)
		ctx.error(tr("Cannot convert units of a non-numerical value."));

	if(targetUnit.isEmpty())
		return v;

	if(v.unit.isEmpty()) {
		v.unit = targetUnit;
		return v;
	}

	UnitList srcunits = matchUnits(v.unit);
	UnitList tgtunits = matchUnits(targetUnit);

	using QS = QSet<const Quantity *>;
	QS qq = iterator(srcunits).mapx(x->quantity).toSet();
	qq.intersect(iterator(tgtunits).mapx(x->quantity).toSet());

	if(qq.isEmpty())
		ctx.error(tr("Cannot convert from '%1' to '%2': units are not of the same quantity.").arg(v.unit, targetUnit));

	if(qq.size() > 1)
		ctx.error(tr("Converting from '%1' to '%2' is ambiguous: could be %3.").arg(v.unit, targetUnit, iterator(qq).mapx(x->name).join(tr(" or "))));

	const Quantity *quantity = *qq.begin();
	const Unit *srcunit = *iterator(srcunits).filterx(x->quantity == quantity);
	const Unit *tgtunit = *iterator(tgtunits).filterx(x->quantity == quantity);

	v.numberValue = v.numberValue * srcunit->coef / tgtunit->coef;
	v.unit = tgtunit->standardForm;
	return v;
}

UnitList UnitManager::matchUnits(const QString &str) const {
	auto &r = unitMatchCache_[str];
	if(r.first)
		return r.second;

	r = {
		true,
		iterator(units_)
			.filterx(x->regex.match(str).capturedLength() == str.length())
			.mapx(static_cast<const Unit *>(x))
			.toList(),
	};

	return r.second;
}

const Quantity *UnitManager::addQuantity(Identifier id, const QString &name) {
	Quantity *q = new Quantity{
		.id = id,
		.name = name,
	};

	quantities_ += q;
	return q;
}

const Unit *UnitManager::addUnit(const QString &standardForm, const Quantity *quantity, double coef, const QString &matchPattern, const Unit::ValueTransformer &valueTransformer) {
	Unit *u = new Unit{
		.standardForm = standardForm,
		.regex = QRegularExpression(matchPattern),
		.coef = coef,
		.quantity = quantity,
		.ix = units_.size(),
		.valueTransformer = valueTransformer,
	};

	units_ += u;
	return u;
}

