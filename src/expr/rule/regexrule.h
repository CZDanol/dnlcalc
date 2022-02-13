#pragma once

#include "rule.h"

namespace Rules {
	template<char... pattern_>
	class Regex : public Rule {
		Q_DECLARE_TR_FUNCTIONS(Regex)

	public:
		static inline const QString pattern = (const char[]) {pattern_..., 0};
		static inline const QString identifier = "__regex_" + pattern;
		static inline const QRegularExpression regex = QRegularExpression(pattern);

	public:
		static RuleUP parse(Parser &p) {
			QRegularExpressionMatch m = regex.match(p.source(), p.pos(), QRegularExpression::NormalMatch, QRegularExpression::AnchorAtOffsetMatchOption);
			if(!m.hasMatch())
				throw Parser::ParseException(tr("Expected '%1'.").arg(pattern));

			auto r = std::make_shared<RegexRule>();
			r->m = m;
			return r;
		}

	public:
		QRegularExpressionMatch m;

	};
}