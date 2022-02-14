#pragma once


struct Unit {

public:
	using ValueTransformer = std::function<QString(ExecutionContext &, double)>;
	static QString defaultValueTransformer(ExecutionContext &ctx, double v);

public:
	QString standardForm;
	QRegularExpression regex;
	double coef;
	const Quantity *quantity;
	qsizetype ix;
	ValueTransformer valueTransformer;

};

