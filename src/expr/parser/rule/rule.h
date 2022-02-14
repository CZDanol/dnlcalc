#pragma once

#include "expr/parser/parser.h"
#include "expr/parser/sourceref.h"

class Rule {

public:
	Rule(bool isError = false) : isError_(isError) {};
	Rule(const Rule &o) = delete;
	virtual ~Rule() = default;

public:
	inline bool isErrorRule() const {
		return isError_;
	}

public:
	SourceRef sourceRef;

private:
	bool isError_;

};
