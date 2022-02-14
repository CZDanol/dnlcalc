#pragma once

#include "expr/exec/value.h"

#include "unit.h"

class UnitManager {
Q_DECLARE_TR_FUNCTIONS(UnitManager);

public:
	~UnitManager();

	void update();

public:
	inline const QRegularExpression &combinedUnitsRegex() const {
		return combinedUnitsRegex_;
	}

public:
	Value convertValue(ExecutionContext &ctx, Value v, const QString &targetUnit) const;

public:
	/// Returns set of units that match the given string
	UnitList matchUnits(const QString &str) const;

public:
	const Quantity *addQuantity(Identifier id, const QString &name);
	const Unit *addUnit(const QString &standardForm, const Quantity *quantity, double coef, const QString &matchPattern, const Unit::ValueTransformer &valueTransformer = &Unit::defaultValueTransformer);

private:
	QList<Unit *> units_;
	QList<Quantity *> quantities_;

private:
	QRegularExpression combinedUnitsRegex_;

private:
	mutable QHash<QString, QPair<bool, UnitList>> unitMatchCache_;

};

