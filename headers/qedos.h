#pragma once

#include <QObject>

class QeDos
{


public:
	QeDos();
	void parseDataNew(const QList<QString>* content);
	void parseAppend(const QList<QString>* content);
	int count(QList<QString>* content);
	void clear();

	QVector<QVector<QVector<double>>> pdos;

	~QeDos();
};
