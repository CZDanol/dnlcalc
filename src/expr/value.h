#pragma once

class Value {

public:
	enum class Type {
		number
	};

public:
	Type type;
	double numberValue;
	QString unit;

};

