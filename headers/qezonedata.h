#pragma once

#include <QVector>
#include <QList>
#include <QTextStream>

class QeZoneData
{
public:
	QeZoneData();
	void parseData(QList<QString>* content);
	void clear();
	QVector<QVector<double>> outputY;
	QVector<QVector<double>> originVector;
	QVector<double> outputX;
};
