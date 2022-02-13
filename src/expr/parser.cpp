#include "parser.h"

#include "rule/rule.h"
#include "rule/errorrule.h"
#include "global.h"

void Parser::setup(const QString &source) {
	source_ = source;
	sourceLen_ = source_.length();
	state_ = {};
}

RuleSP Parser::parse(Identifier rule) {
	qDebug() << "Enter" << state_.pos << rule;

	RuleSP &result = cache_[{state_.pos, rule}];
	if(result) {
		qDebug() << "Found in cache" << rule;
		return result;
	}

	const auto variants = global.rules.ruleVariants(rule);
	if(variants.isEmpty()) {
		qDebug() << "No variants";
		return error(tr("No variants for rule '%1'").arg(rule.str()));
	}

	const State origState = state_;

	// Iteratively try variants of the rule.
	// Stop on first variant match.
	// If no variant matches, return error of the longest match
	// Start at previously attempted rule variant for the same position + 1 to prevent infinite recursion
	qsizetype longestMatch = -1;
	for(qsizetype i = state_.ruleVariantRecursion.value(rule), e = variants.size(); i < e; i++) {
		state_.ruleVariantRecursion[rule] = i + 1;
		auto &v = variants.at(i);
		qDebug() << "Test variant" << i << v->identifier << v->description;

		RuleSP r = v->parse(*this);

		// Found match -> return
		if(!r->isErrorRule()) {
			result = r;
			qDebug() << "Matched variant" << i << state_.pos;
			return r;
		}

		if(state_.pos > longestMatch) {
			longestMatch = state_.pos;
			result = r;
		}

		// Revert to starting state, try another variant of the rule
		state_ = origState;
	}

	qDebug() << "Err longest match" << longestMatch;
	return result;
}

RuleSP Parser::error(const QString &msg) {
	return std::make_shared<Rules::Error>(msg, state_.pos);
}

void Parser::setPos(qsizetype set) {
	assert(set > state_.pos);
	state_.pos = set;

	// Clear rule variant recursion when moving forward
	state_.ruleVariantRecursion.clear();
}

void Parser::skipWhitespace() {
	const qsizetype e = sourceLen_;
	qsizetype i = state_.pos;
	while(i < e && source_.at(i).isSpace())
		i++;

	state_.pos = i;
}
