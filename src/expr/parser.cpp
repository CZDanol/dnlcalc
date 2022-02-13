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
	qDebug().noquote() << state_.debugOffset_ << "Enter" << state_.pos << rule << "\"" << source_.mid(state_.pos) << "\"";

	CacheRec &cr = cache_[{state_.pos, rule}];
	if(cr.rule) {
		qDebug().noquote() << state_.debugOffset_ << "Found in cache" << rule;
		state_.pos = cr.endPos;
		return cr.rule;
	}

	const auto variants = global.rules.ruleVariants(rule);
	if(variants.isEmpty()) {
		qDebug().noquote() << state_.debugOffset_ << "No variants";
		return error(tr("No variants for rule '%1'").arg(rule.str()));
	}

	const State origState = state_;

	// Iteratively try variants of the rule.
	// Stop on first variant match.
	// If no variant matches, return error of the longest match
	// Start at previously attempted rule variant for the same position + 1 to prevent infinite recursion
	for(qsizetype i = state_.ruleVariantRecursion.value(rule), e = variants.size(); i < e; i++) {
		state_.ruleVariantRecursion[rule] = i + 1;
		state_.debugOffset_ += "  ";

		auto &v = variants.at(i);
		qDebug().noquote() << state_.debugOffset_ << "Test variant" << i << v->identifier << v->description;

		state_.debugOffset_ += "  ";

		RuleSP r = v->parse(*this);

		// Found match -> return
		if(!r->isErrorRule()) {
			cr.rule = r;
			cr.endPos = state_.pos;
			qDebug().noquote() << state_.debugOffset_ << "Matched variant" << i << state_.pos;
			state_.debugOffset_ = origState.debugOffset_;
			return r;
		}

		if(state_.pos > cr.endPos) {
			cr.rule = r;
			cr.endPos = state_.pos;
		}

		// Revert to starting state, try another variant of the rule
		state_ = origState;
	}

	qDebug().noquote() << state_.debugOffset_ << "Err longest match" << cr.endPos;
	state_.debugOffset_ = origState.debugOffset_;
	return cr.rule;
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
