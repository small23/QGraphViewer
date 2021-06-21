#ifndef SURFDATA_H
#define SURFDATA_H

#include <QVector>
#include <QList>
#include <QTextStream>

//Класс-хранилище данных поверхностей

class SurfData
{
public:
    SurfData();
    QVector<double> oX, oY, oRepeatX, oRepeatY, oF;
    //QVector<QVector<double>> oF;
    //Парсер данных
    void parseData(QList<QString> *content);
    //Поворот данных на угол 0-270 градусов
    void rotateData(int angle);
    void clear();
};

#endif // SURFDATA_H
