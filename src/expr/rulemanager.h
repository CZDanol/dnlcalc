#pragma once

#include "rule/compositeexpressionrule.h"

class RuleManager {

public:
	~RuleManager();

public:
	template<typename T>
	void addRule() {
		rules_[T::identifier] += new RuleRefT<T>();
	}

	template<auto F>
	inline void addExpression() {
		auto helper = [this] <typename ...Args > (const std::function<Value(Args...)> &) {
			addRule<Rules::CompositeExpression<F, Args...>>();
		};
		helper(F);
	}

private:
	struct RuleRef {
		virtual const QString &identifier() const = 0;
		virtual RuleSP parse(Parser &p) = 0;
	};
	template<typename T>
	struct RuleRefT : public RuleRef {
		static const inline QString identifierStatic = T::identifier;

		virtual const QString &identifier() const override { return identifierStatic; }

		virtual RuleSP parse(Parser &p) override { return T::parse(p); }
	};

private:
	QHash<QString, QList<RuleRef *>> rules_;

};

