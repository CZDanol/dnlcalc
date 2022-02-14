#pragma once

#include "regexrule.h"

namespace Rules {

	class Unit : public Rule {
	Q_DECLARE_TR_FUNCTIONS(Unit)

	public:
		static inline const QString description = QStringLiteral("Unit");

	public:
		static RuleSP parse(Parser &p);

	public:
		QString str;

	};

}