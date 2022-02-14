#include "unitrule.h"

#include "global.h"

RuleSP Rules::Unit::parse(Parser &p) {
	QRegularExpressionMatch m = global.units.combinedUnitsRegex().match(p.source(), p.pos(), QRegularExpression::NormalMatch, QRegularExpression::AnchorAtOffsetMatchOption);
	if(!m.hasMatch())
		return p.error(tr("Expected unit."));

	p.setPos(m.capturedEnd());

	auto r = std::make_shared<Unit>();
	r->str = m.captured(0);
	return r;
}
