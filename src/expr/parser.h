#pragma once

class Parser {
Q_DECLARE_TR_FUNCTIONS(Parser)

public:
	void setup(const QString &source);

public:
	inline const QString &source() const {
		return source_;
	}

	/// Position in source for the currently parsed rule
	inline qsizetype pos() const {
		return state_.pos;
	}

public:
	/// Parse rule at the current position for the current source
	RuleSP parse(Identifier rule);

	template<typename T>
	inline RuleSP parse() {
		return parse(T::identifier);
	}

	RuleSP error(const QString &msg);

	/// Sets the position to somewhere else
	void setPos(qsizetype set);

	void skipWhitespace();

private:
	QString source_;
	qsizetype sourceLen_;

private:
	struct State {
		qsizetype pos = 0;
		Identifier recursionRule;
		qsizetype ruleRecursion = 0;
	};
	State state_;

public:
	struct CacheKey {
		qsizetype pos;
		Identifier rule;
		qsizetype variant;

		bool operator ==(const CacheKey &o) const = default;
	};
	struct CacheRec {
		RuleSP rule;
		qsizetype endPos;
	};

private:
	/// Cache of already parsed rules at various positions (so they don't have to be parsed multiple times)
	QHash<CacheKey, CacheRec> cache_;

};

inline size_t qHash(const Parser::CacheKey &c, size_t seed = 0) {
	return qHashMulti(seed, c.pos, c.rule, c.variant);
}
