#pragma once

#include "rule.h"
#include "util/stringutils.h"

namespace Rules {

	template<StaticString pattern_>
	class Regex : public Rule {
	Q_DECLARE_TR_FUNCTIONS(Regex)

	public:
		static inline const QString pattern = pattern_.toString();
		static inline const Identifier identifier = Identifier::fromString("__regex_" + pattern);
		static inline const QString description = QStringLiteral("Regex(%1)").arg(pattern);
		static inline const QRegularExpression regex = QRegularExpression(pattern);

	public:
		static RuleSP parse(Parser &p) {
			QRegularExpressionMatch m = regex.match(p.source(), p.pos(), QRegularExpression::PartialPreferCompleteMatch, QRegularExpression::AnchorAtOffsetMatchOption);
			if(m.hasMatch() || m.hasPartialMatch())
				p.setPos(m.capturedEnd());

			if(!m.hasMatch())
				return p.error(tr("Expected '%1'.").arg(pattern));

			auto r = std::make_shared<Regex>();
			r->m = m;
			return r;
		}

	public:
		QRegularExpressionMatch m;

	};

}