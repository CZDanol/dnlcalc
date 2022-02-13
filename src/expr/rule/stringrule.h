#pragma once

#include "rule.h"
#include "util/stringutils.h"

namespace Rules {

	template<StaticString str_>
	class String : public Rule {
		Q_DECLARE_TR_FUNCTIONS(String)

	public:
		static inline const QString str = str_.toString();
		static inline const Identifier identifier = Identifier::fromString("__str_" + str);
		static inline const QString description = QStringLiteral("String(%1)").arg(str);

	public:
		static RuleSP parse(Parser &p) {
			if(p.source().mid(p.pos(), str.length()) != str)
				return p.error(tr("Expected '%1'.").arg(str));

			return std::make_shared<String>();
		}

	};

}