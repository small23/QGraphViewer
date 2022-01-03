// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#pragma once

#include <QObject>
#include <QMap>

//Класс-словарь математических символов, присутствующих в юникоде

class MathSymbols final : public QObject
{
	Q_OBJECT

public:
	explicit MathSymbols(QObject *parent);
	QString adaptString(QString rawString) const;
	~MathSymbols();
	void initMap() const;
	QMap<QString, QString> *map;
};
