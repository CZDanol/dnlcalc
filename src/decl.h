#pragma once

#include <memory>

class RuleManager;
class FunctionManager;
class UnitManager;

class Parser;
class Rule;

class ExecutionContext;

using RuleSP = std::shared_ptr<const Rule>;