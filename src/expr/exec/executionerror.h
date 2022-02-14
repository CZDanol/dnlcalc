#pragma once


class ExecutionError : public std::exception {

public:
	ExecutionError(const QString &msg) : msg(msg) {}

public:
	QString msg;

};

