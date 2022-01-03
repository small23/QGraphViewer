// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#ifndef PLOTPARAMETERS_H
#define PLOTPARAMETERS_H

//Класс-хранилище настроек построения графиков

#include <QWidget>
#include "ui_mainwindow.h"
#include "qcustomplot.h"

class PlotParameters : public QWidget
{
    Q_OBJECT
public:
    //Конструктор класса, передается указатель на форму для чтения параметров
    explicit PlotParameters(Ui::MainWindow *ui, QWidget *parent);
    //Обновляет параметры построения с указаной вкладки
    void updatePlotParams(int tabId);
    //Обновления цвета линии
    void updateColors(int colorId, const QColor& color);
    void setCountOfLines(int size) const;
    //Структура-хранилище настроек каждой линии
    struct UniversalLineParams{
        qreal width;
        Qt::PenStyle style;
        QColor color;
        QCPScatterStyle pointStyle;
        int styleId;
        bool show;
        double multiplier;
    };
    //Вторичные параметры построения
    UniversalLineParams tab1PlotParams[7];
    QVector<UniversalLineParams> *tab2PlotParams;
    QColor tab2FermiLevel;
    double tab2FermiLevelWidth;
    bool tab2ShowFermiLine;
    QString tab2PlotName="";
    QString tab2OyName="";
    QString tab2OxName="";
    bool tab2OyTicks;
    bool tab2OxTicks;
    bool tab2ShowOx;
    bool tab2FxInverse;
    double tab1surfaceDivider;
    double tab1surfacePrecision;
    double tab1surfaceWidth;
    bool tab2zeroShift;
    bool commonUhf;
	bool colorContours;
    int drawRes;
    int drawQuality=90;
    double drawScale=6;
    int preferFormat=0;

    QVector<UniversalLineParams>* tab5PlotParams;
    QColor tab5FermiLevelColor;
    double tab5FermiLevelWidth;
    bool tab5ShowFermiLine;
    double tab5FermiLevel;
    QString tab5PlotName = "";
    QString tab5OyName = "";
    QString tab5OxName = "";
    bool tab5OyTicks;
    bool tab5OxTicks;
    double tab5xMin;
    double tab5xMax;
    double tab5yMin;
    double tab5yMax;
    double tab5yMinZs;
    double tab5yMaxZs;


private:
    Ui::MainWindow *ui;
    QWidget *parent;



};

#endif // PLOTPARAMETERS_H
