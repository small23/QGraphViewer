#include "QeDos.h"

#include <qvector2d.h>
#include <QtCore/qtextstream.h>

QeDos::QeDos()
{

}

void QeDos::parseData(QList<QString>* content)
{
	pdos.clear();
	int a = 0;
	a++;

	QString test = content->at(1);
	QStringList test2 = test.split(" ");
	int i = test2.count()-1;
	while (i>=0)
	{
		if (test2.at(i) == "")
			test2.removeAt(i);
		i--;
	}

	int numbersCount = test2.count();

	
	for (int i=1; i<content->size(); i++)
	{
		QString c = content->at(i);
		if (c=="")
			continue;
		pdos.append(QVector<double>(numbersCount));
		QTextStream getData(&c);
		double x;
		for (int j=0; j<numbersCount; j++)
		{
			getData >> x;
			pdos[i - 1][j] = x;
		}
	}

}

void QeDos::clear()
{
	
}

QeDos::~QeDos()
{
}
