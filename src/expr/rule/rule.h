#pragma once

#include "expr/parser.h"

class Rule {

public:
	Rule(bool isError = false) : isError_(isError) {};
	Rule(const Rule &o) = delete;
	virtual ~Rule() = default;

public:
	inline bool isErrorRule() const {
		return isError_;
	}

private:
	bool isError_;

};
