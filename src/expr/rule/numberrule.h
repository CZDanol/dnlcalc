#pragma once

#include "rule.h"

namespace Rules {
	class Number : public Rule {
		Q_DECLARE_TR_FUNCTIONS(Number)

	public:
		static inline const QString identifier = "Number";

	public:
		static RuleSP parse(Parser &p) {
			static const QRegularExpression regex("[0-9]+([,.][0-9]+)?|[.,][0-9]+");
			QRegularExpressionMatch m = regex.match(p.source(), p.pos(), QRegularExpression::NormalMatch, QRegularExpression::AnchorAtOffsetMatchOption);
			if(!m.hasMatch())
				throw Parser::ParseException(tr("Expected number.").arg(regex.pattern()));

			QString s = m.captured().replace(',', '.');
			auto r = std::make_shared<Number>();
			r->v = s.toDouble();
			return r;
		}

	public:
		double v;

	};
}