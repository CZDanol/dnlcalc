#include "functionmanager.h"

#include "expr/exec/executioncontext.h"
#include "expr/exec/executionerror.h"
#include "util/iterator.h"

FunctionManager::~FunctionManager() {
	for(const auto &o: functions_)
		qDeleteAll(o);
}

Value FunctionManager::functionCall(ExecutionContext &ctx, Identifier func, const QList<Value> &args) {
	auto overloads = functions_.value(func);

	// No overload -> function not defined
	if(overloads.isEmpty())
		ctx.error(tr("Function '%1' is not defined.").arg(func.str()));

	// Single overload -> go just straight to the error
	if(overloads.size() == 1)
		overloads.first()->call(ctx, args);

	for(const auto &o: overloads) {
		try {
			return o->call(ctx, args);
		}
		catch(const ExecutionError &e) {

		}
	}

	ctx.error(tr("No overloads of function '%1' match arguments (%2)").arg(func.str(), iterator(args).mapx(x.matchString()).join(", ")));
}
