#include "number.h"

ArgsMatching::Number ArgsMatching::Number::match(ExecutionContext &ctx, const QList<Value> &args, qsizetype &i) {
	if(i >= args.length())
		ctx.error(tr("Not enough arguments."));

	const Value &v = args.at(i++);
	switch(v.type) {

		case Type::number: {
			Number r;
			static_cast<Value&>(r) = v;
			return r;
		}

		default:
			ctx.error(tr("Expected number."));

	}
}
