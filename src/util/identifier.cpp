#include "identifier.h"

#include <QReadWriteLock>
#include <QDebug>

struct SharedData {
	QReadWriteLock mutex;
	QHash<QString, Identifier::Handle> map;
	QVector<QString> list = {QString()};
};
static inline SharedData &sharedData() {
	static SharedData d;
	return d;
}

Identifier Identifier::fromString(const QString &str) {
	if(str.isEmpty())
		return {};

	auto &r = sharedData();

	{
		QReadLocker _l(&r.mutex);
		if(Handle h = r.map.value(str))
			return Identifier(h);
	}

	{
		QWriteLocker _l(&r.mutex);

		Handle &h = r.map[str];
		if(h)
			return Identifier(h);

		h = r.list.size();
		r.list += str;

		return Identifier(h);
	}
}

void Identifier::debugPrintList() {
	auto &r = sharedData();

	QReadLocker _rl(&r.mutex);
	qDebug() << "IDENTIFIERS LIST BEGIN";
	for(int i = 0; i < r.list.size(); i++)
		qDebug() << i << ": " << r.list.at(i);

	qDebug() << "IDENTIFIERS LIST END";
}

QString Identifier::str() const {
	auto &r = sharedData();

	QReadLocker _rl(&r.mutex);
	return r.list.at(data_);
}
