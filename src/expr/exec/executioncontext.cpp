#include "executioncontext.h"
#include "executionerror.h"

#include "global.h"

void ExecutionContext::error(const QString &msg) {
	throw ExecutionError(msg);
}

Value ExecutionContext::functionCall(Identifier func, const QList<Value> &args) {
	return global.functions.functionCall(*this, func, args);
}
