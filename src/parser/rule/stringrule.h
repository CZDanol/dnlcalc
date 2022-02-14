#pragma once

#include "rule.h"
#include "util/stringutils.h"

namespace Rules {

	template<StaticString str_>
	class String : public Rule {
		Q_DECLARE_TR_FUNCTIONS(String)

	public:
		static inline const QString str = str_.toString();
		static inline const qsizetype strLentgh = str.length();
		static inline const QString description = QStringLiteral("String(\"%1\")").arg(str);

	public:
		static RuleSP parse(Parser &p) {
			if(p.source().mid(p.pos(), strLentgh) != str)
				return p.error(tr("Expected '%1'.").arg(str));

			p.setPos(p.pos() + strLentgh);
			return std::make_shared<String>();
		}

	};

}
