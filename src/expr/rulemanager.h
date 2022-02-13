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
		auto helper = [this] <typename ...Args > (Value (*)(const Args&...)) {
			addRule<Rules::CompositeExpression<F, Args...>>();
		};
		helper(F);
	}

private:
	struct RuleRef {
		virtual Identifier identifier() const = 0;
		virtual RuleSP parse(Parser &p) = 0;
	};
	template<typename T>
	struct RuleRefT : public RuleRef {
		static const inline Identifier identifierStatic = T::identifier;

		virtual Identifier identifier() const override { return identifierStatic; }

		virtual RuleSP parse(Parser &p) override { return T::parse(p); }
	};

private:
	QHash<Identifier, QList<RuleRef *>> rules_;

};

