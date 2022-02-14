#include "intrinsicfunctions.h"

#include "expr/function/functionmanager.h"
#include "expr/function/match/number.h"

void loadIntrinsicFunctions(FunctionManager &mgr) {
	using namespace ArgsMatching;
	using C = ExecutionContext;

	mgr.addFunction<"add"_S, +[](C &ctx, Number a, Number b) {
		return Value{
			.type = ValueType::number,
			.numberValue = a.asNumber() + b.asNumber(),
		};
	}>();
}
