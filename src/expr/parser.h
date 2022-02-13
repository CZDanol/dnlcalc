#pragma once

class Parser {

public:
	class ParseException : public std::exception {

	public:
		inline ParseException(const QString &msg) : msg(msg) {}

	public:
		QString msg;

	};

public:
	inline const QString &source() const {
		return source_;
	}

	/// Position in source for the currently parsed rule
	inline qsizetype pos() const {
		return pos_;
	}

	/// Sets the position to somewhere else
	inline void setPos(qsizetype set) {
		pos_ = set;
	}

public:
	RuleSP parse(const QString &rule);

private:
	QString source_;
	qsizetype pos_;

};

