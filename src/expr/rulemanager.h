#pragma once

#include "rule/compositeexpressionrule.h"

class RuleManager {

public:
	~RuleManager();

public:
	inline auto ruleVariants(Identifier rule) const {
		return rules_.value(rule);
	}

public:
	template<typename T>
	void addRule() {
		rules_[T::identifier] += new RuleRefT<T>();
	}

	template<auto F>
	inline void addExpression() {
		auto helper = [this] <typename... Args > (Value (*)(const Args &...)) {
			addRule<Rules::CompositeExpression<F, Args...>>();
		};
		helper(F);
	}

private:
	struct RuleRef {
		Identifier identifier;
		QString description;
		virtual RuleSP parse(Parser &p) = 0;
	};
	template<typename T>
	struct RuleRefT : public RuleRef {
		RuleRefT() {
			identifier = T::identifier;
			description = T::description;
		}

		virtual RuleSP parse(Parser &p) override { return T::parse(p); }
	};

private:
	QHash<Identifier, QList<RuleRef *>> rules_;

};

