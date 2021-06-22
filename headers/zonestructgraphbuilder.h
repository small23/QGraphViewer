#ifndef ZONESTRUCTGRAPHBUILDER_H
#define ZONESTRUCTGRAPHBUILDER_H

//Класс отрисовки графика с данными зонных структур

#include <QObject>
#include <QWidget>
#include "qcustomplot.h"
#include "QFont"
#include "banddata.h"
#include "plotparameters.h"
#include "SettingsKeeper.h"
#include "mathsymbols.h"

class ZoneStructGraphBuilder : public QWidget
{
    Q_OBJECT
public:
    //Конструктор класса, после выполнения отрисовывает окно графика
    //graphics - координаты линий для построения
    //params - данные построения (ширина\цвет линий, тип линии и т.д.)
    //font - шрифт, которым будут отображаться текст
    //settings - передача последних испольхованых путей и настроек сохранения изображения
    //min max - ограничения диапазона отображения
    //kPoints - имена к-точек
    //buildNumbers - ограничители уровня ферми
    explicit ZoneStructGraphBuilder(BandData *graphics, double min, double max, QString kPoints, PlotParameters *params, QFont font,
                                    double buildNumbers[2], QString title, SettingsKeeper* settings, MathSymbols *symbols, QWidget *parent = nullptr);

	//~ZoneStructGraphBuilder();
	
private slots:
    //Слоты для обработки эвентов от мыши
    //Вызов навигационного меню
    void contextMenuRequest(QPoint pos);
    //Обработка эвента сохранения изображения
    void savePicture();
    void deletionOnClose();
private:
    QCustomPlot *customPlot;
    PlotParameters* plotParams;
    QWidget* parent;
    SettingsKeeper* settings;
};

#endif // ZONESTRUCTGRAPHBUILDER_H
