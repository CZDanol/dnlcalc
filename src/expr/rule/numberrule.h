#pragma once

#include "rule.h"
#include "errorrule.h"

namespace Rules {

	class Number : public Rule {
		Q_DECLARE_TR_FUNCTIONS(Number)

	public:
		static inline const Identifier identifier = "Number"_ID;

	public:
		static RuleSP parse(Parser &p) {
			static const QRegularExpression regex("-?([0-9]+([,.][0-9]+)?|[.,][0-9]+)");
			QRegularExpressionMatch m = regex.match(p.source(), p.pos(), QRegularExpression::NormalMatch, QRegularExpression::AnchorAtOffsetMatchOption);

			if(m.hasMatch() || m.hasPartialMatch())
				p.setPos(m.capturedEnd());

			if(m.hasPartialMatch())
				return p.error(tr("Expected decimal number part after '.' or ','."));

			if(!m.hasMatch())
				return p.error(tr("Expected number."));

			QString s = m.captured().replace(',', '.');
			auto r = std::make_shared<Number>();
			r->v = s.toDouble();
			return r;
		}

	public:
		double v;

	};

}