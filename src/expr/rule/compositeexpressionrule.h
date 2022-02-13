#pragma once

#include "expressionrule.h"

namespace Rules {
	template<auto func, typename... Elements>
	class CompositeExpression final : public Expression {

	public:
		static RuleSP parse(Parser &p) {
			auto elements = std::tuple{p.parse(Elements::identifier)...};

			auto r = std::make_shared<CompositeExpression>();
			r->elements = std::move(elements);
			return r;
		}

		virtual Value exec() const override {
			size_t i = 0;
			return std::apply(func, std::tuple{*static_cast<Elements * > (elements[i++].get())...});
		}

	public:
		std::vector<RuleSP> elements;

	};
}