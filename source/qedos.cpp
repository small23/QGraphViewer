// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "qedos.h"

QeDos::QeDos()
= default;

void QeDos::parseDataNew(const QList<QString>* content)
{
	clear();
	parseAppend(content);
}

void QeDos::parseAppend(const QList<QString>* content)
{
	pdos.append(QVector<QVector<double>>(1));
	const int index = pdos.count() - 1;
	const int numbersCount = count(content)+1;

	pdos[index].clear();
	for (int i = 1; i < content->size(); i++)
	{
		QString c = content->at(i);
		if (c == "")
			continue;
		pdos[index].append(QVector<double>(numbersCount));
		QTextStream getData(&c);
		double x;
		for (int j = 0; j < numbersCount; j++)
		{
			getData >> x;
			pdos[index][i - 1][j] = x;
		}
	}
}



int QeDos::count(const QList<QString>* content)
{
	QString test = content->at(1);
	QStringList test2 = test.split(" ");
	int i = test2.count() - 1;
	while (i >= 0)
	{
		if (test2.at(i) == "")
			test2.removeAt(i);
		i--;
	}

	return test2.count()-1;
}

void QeDos::clear()
{
	for (auto vect : pdos)
	{
		for (auto data : vect)
		{
			data.clear();
		}
		vect.clear();
	}
	pdos.clear();
}

QeDos::~QeDos()
= default;
