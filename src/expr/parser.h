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

		/// To prevent infinite left recursion, when testing the same rule on the same position multiple times, next time test only variants that have not been tested yet
		QMap<Identifier, qsizetype> ruleVariantRecursion;

		QString debugOffset_;
	};
	State state_;

private:
	struct CacheRec {
		RuleSP rule;
		qsizetype endPos;
	};

	/// Cache of already parsed rules at various positions (so they don't have to be parsed multiple times)
	QHash<QPair<qsizetype, Identifier>, CacheRec> cache_;

};

