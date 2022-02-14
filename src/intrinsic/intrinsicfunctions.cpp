#include "intrinsicfunctions.h"

#include "global.h"

#include "expr/function/functionmanager.h"
#include "expr/function/match/number.h"

void loadIntrinsicFunctions(FunctionManager &mgr) {
	using namespace ArgsMatching;
	using C = ExecutionContext;

	mgr.addFunction<"add"_S, +[](C &ctx, Number a, Number b) {
		return Value{
			.type = ValueType::number,
			.numberValue = a.asNumber() + global.units.convertValue(ctx, b, a.unit).asNumber(),
			.unit = a.unit
		};
	}>();
	mgr.addFunction<"sub"_S, +[](C &ctx, Number a, Number b) {
		return Value{
			.type = ValueType::number,
			.numberValue = a.asNumber() - global.units.convertValue(ctx, b, a.unit).asNumber(),
			.unit = a.unit
		};
	}>();

	// Todo: units for mult & div
	mgr.addFunction<"mult"_S, +[](C &ctx, Number a, Number b) {
		return Value{
			.type = ValueType::number,
			.numberValue = a.asNumber() * b.asNumber(),
		};
	}>();
	mgr.addFunction<"div"_S, +[](C &ctx, Number a, Number b) {
		return Value{
			.type = ValueType::number,
			.numberValue = a.asNumber() / b.asNumber(),
		};
	}>();
}
