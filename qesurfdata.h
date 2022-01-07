#pragma once
#include <QVector>
#include <QList>
#include <QTextStream>

class QeSurfData 
{


public:
	QeSurfData();
    QVector<double> oX, oY, oRepeatX, oRepeatY, oF;
    //QVector<QVector<double>> oF;
    //Парсер данных
    void parseData(QList<QString>* content);
	//Поворот данных на угол 0-270 градусов
    void rotateData(int angle);
    void clear();
};
