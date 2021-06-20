#pragma once

#include <QObject>
#include <QMap>

//Класс-словарь математических символов, присутствующих в юникоде

class MathSymbols : public QObject
{
	Q_OBJECT

public:
	MathSymbols(QObject *parent);
	~MathSymbols();
	void initMap();
	QMap<QString, QString> *map;
};
