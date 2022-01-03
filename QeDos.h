#pragma once

#include <QObject>

class QeDos
{


public:
	QeDos();
	void parseData(QList<QString>* content);
	void clear();

	QVector<QVector<double>> pdos;

	~QeDos();
};
