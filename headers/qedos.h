#pragma once

#include <QObject>
#include <QtCore/qtextstream.h>

class QeDos
{


public:
	QeDos();
	void parseDataNew(const QList<QString>* content);
	void parseAppend(const QList<QString>* content);
	int count(const QList<QString>* content);
	void clear();

	QVector<QVector<QVector<double>>> pdos;

	~QeDos();
};
