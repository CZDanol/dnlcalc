#pragma once

class Value {

public:
	enum class Type {
		number
	};

public:
	double asNumber() const;

public:
	QString displayString() const;

public:
	Type type;
	double numberValue;
	QString unit;

};

