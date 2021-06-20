#ifndef STRUCTURESHEADERS_H
#define STRUCTURESHEADERS_H
#include <QColor>
#include <qcustomplot.h>

//Хедер-декларатор стандартных структур данных

struct UniversalLines{
    QVector<double> x;
    QVector<double> y;
    int Type;
};

struct UniversalPoints{
    double x;
    double y;
    int Type;
};

struct UniversalLineParams{
    qreal width;
    Qt::PenStyle style;
    QColor color;
    QCPScatterStyle pointStyle;
};

struct AtomTypes
{
    int number;
    QString name;
    QString type;
    int begin;
    int end;
};
#endif // STRUCTURESHEADERS_H
