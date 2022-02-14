#pragma once


struct Quantity {
	Identifier id;
	QString name;
	QList<const Unit*> units;
};

