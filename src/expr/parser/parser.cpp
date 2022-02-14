#include "parser.h"

#include "expr/parser/rule/rule.h"
#include "expr/parser/rule/errorrule.h"
#include "global.h"
#include "util/valueguard.h"

void Parser::setup(const QString &source) {
	source_ = source;
	sourceLen_ = source_.length();
	state_ = {};
}

RuleSP Parser::parse(Identifier rule) {
	ValueGuard _vg(state_.recursion);

	const qsizetype startPos = state_.pos;

	const qsizetype recursion = state_.recursion.value(rule);
	const CacheKey cacheKey{state_.pos, rule, recursion};

	RuleSP r = cache_.value(cacheKey);
	if(r) {
		setPos(r->sourceRef.end);
		return r;
	}

	const auto variants = global.rules.ruleVariants(rule);
	if(variants.isEmpty())
		return error(tr("No variants for rule '%1'").arg(rule.str()));

	const State origState = state_;

	// Iteratively try variants of the rule.
	// Stop on first variant match.
	// If no variant matches, return error of the longest match
	// Start at previously attempted rule variant for the same position + 1 to prevent infinite recursion
	for(qsizetype i = recursion, e = variants.size(); i < e; i++) {
		state_.recursion[rule] = i + 1;

		const auto &v = variants.at(i);
		RuleSP pr = v->parse(*this);

		const_cast<SourceRef &>(pr->sourceRef) = SourceRef{
			.start = startPos,
			.end = state_.pos,
		};

		// Found match -> return
		if(!pr->isErrorRule()) {
			cache_[cacheKey] = pr;
			return pr;
		}

		if(state_.pos >= pr->sourceRef.end)
			pr = r;

		// Revert to starting state, try another variant of the rule
		state_ = origState;
	}

	assert(r);
	cache_[cacheKey] = r;
	return r;
}

RuleSP Parser::error(const QString &msg) {
	return std::make_shared<Rules::Error>(msg, state_.pos);
}

void Parser::setPos(qsizetype set) {
	assert(set >= state_.pos);
	state_.pos = set;
}

void Parser::skipWhitespace() {
	const qsizetype e = sourceLen_;
	qsizetype i = state_.pos;
	while(i < e && source_.at(i).isSpace())
		i++;

	if(i != state_.pos)
		setPos(i);
}
