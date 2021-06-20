#ifndef DOSGRAPHBUILDER_H
#define DOSGRAPHBUILDER_H

//Класс отрисовки графиков DOS линий

#include <QObject>
#include <QWidget>
#include "qcustomplot.h"
#include "QFont"
#include "banddata.h"
#include "plotparameters.h"
#include "SettingsKeeper.h"
#include "mathsymbols.h"

class DOSGraphBuilder : public QWidget
{
    Q_OBJECT
public:
    //Конструктор класса, graphics - данные для построения
    //borders - границы построения X Y, задаваемые в интерфейсе
    //params - параметры построений (ширина\цвет линий и т.д.)
    //angle - угол поворота графика (-90..0..90 градусов)
    //settings - хранение путей сохранения изображений
    //currentGraphic - текущий выбранный график в окне выбора
    explicit DOSGraphBuilder(BandData* graphics, double borders[4], PlotParameters* params, QFont font,int angle,SettingsKeeper* settings, MathSymbols *symbols, int currentGraphic, QWidget* parent = nullptr);

private slots:
    //Слоты для обработки эвентов от мыши
    //Вызов навигационного меню
    void contextMenuRequest(QPoint pos);
    //Обработка эвента сохранения изображения
    void savePicture();

private:
    //Метод отрисовки данных на графике
    void drawData(QVector<QVector<double>> data, QVector<double> axis, PlotParameters* params, int angle, int
                  paramsShift, bool* showed);
    QCustomPlot *customPlot;
    PlotParameters* plotParams;
    QWidget* parent;
    SettingsKeeper* settings;
};

#endif // DOSGRAPHBUILDER_H
