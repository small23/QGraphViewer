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
    void resizeEvent(QResizeEvent* event) override;
    void showEvent(QShowEvent* event) override;
    void closeEvent(QCloseEvent* event) override;

protected:
    void drawDataIsolines(std::vector<MarchingSquares::levelPaths> result, double* hslA, double* hslB,
        const double* hslAStep, const double* hslBStep, const QVector<double>& oXTemp,
        const QVector<double>& oYTemp, bool shiftA, bool shiftB,
        int angle, double stepX, double stepY, double surfaceWidth, bool colorLines) const;

        SettingsKeeper* settings;
        QWidget* parent;
        //Множитель разрешения для корректной работы на нестандартном
        //DPI\масштабировании системы
        double compareScale = 1;
        QCustomPlot *customPlot;
        PlotParameters* plotParams;
        QVBoxLayout* vbl;
        QPixmap plotDraw;
        int plotWidth;
        int plotHeight;
        QFont font;
        QWidget window;
        QLabel imageOnWidget;
};

#endif // GRAPHBUILDER_H
