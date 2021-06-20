#ifndef BASICGRAPHBUILD_H
#define BASICGRAPHBUILD_H

//Класс отрисовки графика с данными Trajgrad\Molgraph

#include <QObject>
#include <QWidget>
#include "qcustomplot.h"
#include "graphicsdata.h"
#include "QFont"
#include "plotparameters.h"
#include "surfdata.h"
#include "banddata.h"
#include "contour.h"
#include "SettingsKeeper.h"

class BasicGraphBuild : public QWidget
{
    Q_OBJECT
public:
    //Конструктор класса, после выполнения отрисовывает окно графика
    //plotParams - данные построения (ширина\цвет линий, тип линии и т.д.)
    //font - шрифт, которым будут отображаться текст
    //showAxis - переменая показа осей на графике
    //buildtype - Тип графика MAPN (при наличии)
    //UHF - режим обработки данных
    //settings - передача последних испольхованых путей и настроек сохранения изображения
    //data, surfaveData, bandData - данные для отрисовки
    //angle - угол поворота графика
    explicit BasicGraphBuild(PlotParameters *plotParams, const QFont& font,bool showAxis, int buildtype,bool uhf, SettingsKeeper* settings,
        GraphicsData *data, SurfData *surfaceData, BandData *bandData, int angle,QWidget *parent = nullptr);

private slots:
    //Слоты для обработки эвентов от мыши
    //Вызов навигационного меню
    void contextMenuRequest(QPoint pos);
    //Обработка эвента сохранения изображения
    void savePicture();

private:
    QWidget* parent;
    //Множитель разрешения для корректной работы на нестандартном
    //DPI\масштабировании системы
    double CompareScale;
    QCustomPlot *customPlot;
    PlotParameters* plotParams;
    //Внутренние методы отрисовки различных данных
    void draw_surface(SurfData* surfData, PlotParameters* plotParams, int angle);
    void draw_band(BandData* bandData, PlotParameters* plotParams, int buildType, bool uhf, int angle);
    void draw_data_isolines(PlotParameters* plotParams,
                            std::vector<MarchingSquares::levelPaths> result,
                            double* hslA, double* hslB, double* hslAStep, double* hslBStep, const QVector<double>& oXTemp,
                            const QVector<double>& oYTemp, bool
                            shiftA, bool shiftB, int hslABorder, int hslBBorder, int angle, double stepX, double stepY);
    void drawDataLines(PlotParameters* plotParams, QList<UniversalLines>* Trajgrad, int index, int angle);
    SettingsKeeper* settings;

};

#endif // BASICGRAPHBUILD_H
