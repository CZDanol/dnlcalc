#pragma once

#include "rule.h"

namespace Rules {

	class Error : public Rule {

	public:
		Error(const QString &msg, qsizetype pos) : Rule(true), msg_(msg), pos_(pos) {}

	public:
		inline const QString &msg() const {
			return msg_;
		}

		inline qsizetype pos() const {
			return pos_;
		}

	private:
		QString msg_;
		qsizetype pos_;

	};

}