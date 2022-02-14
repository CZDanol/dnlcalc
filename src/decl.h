#pragma once

#include <memory>

class Parser;
class Rule;
class RuleManager;

class ExecutionContext;

using RuleSP = std::shared_ptr<const Rule>;