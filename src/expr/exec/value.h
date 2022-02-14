#pragma once

#include "valuetype.h"

struct Value {

public:
	using Type = ValueType;

public:
	double asNumber() const;

public:
	/// String displayed in the result field
	QString displayString(ExecutionContext &ctx) const;

	/// String displayed on match error (should mainly show type)
	QString matchString() const;

public:
	Type type = Type::unknown;

public:
	double numberValue;

	/// Unit, in the raw input formet (as was)
	QString unit;

public:
	QString error;

public:
	Value &operator =(const Value &o) = default;

};
