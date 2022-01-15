#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include "qcustomplot.h"
#include "QFont"
#include "plotparameters.h"
#include "contour.h"
#include "settingskeeper.h"
#include "constantsandstrings.h"

class GraphBuilder : public QWidget
{
    Q_OBJECT
public:
    GraphBuilder(SettingsKeeper* settings, const QString& title, PlotParameters* plotParams, const QFont& font, QWidget* parent = nullptr);
    virtual void draw();
    int plotType = 0;

public slots:
    //Слоты для обработки эвентов от мыши
    //Вызов навигационного меню
    void contextMenuRequest(QPoint pos);
    //Обработка эвента сохранения изображения
    void savePicture();
    void deletionOnClose(QObject* obj);

protected:
        SettingsKeeper* settings;
        QWidget* parent;
        //Множитель разрешения для корректной работы на нестандартном
        //DPI\масштабировании системы
        double compareScale{};
        QCustomPlot *customPlot;
        PlotParameters* plotParams;
        QFont font;
};

#endif // GRAPHBUILDER_H
