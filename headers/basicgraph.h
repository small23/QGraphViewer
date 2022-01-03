#ifndef BASICGRAPH_H
#define BASICGRAPH_H

#include "banddata.h"
#include "graphbuilder.h"
#include "graphicsdata.h"
#include "surfdata.h"

class BasicGraph final :GraphBuilder
{
public:
    BasicGraph(SettingsKeeper* settings, const QString& title, PlotParameters* plotParams, QFont font, QWidget *parent = nullptr);
    virtual void draw(const bool hideAxis,
                      const int buildType, const bool uhf, GraphicsData* graphics,
                      SurfData* surfaceData, BandData* bandData, const int angle);

private:
    //Внутренние методы отрисовки различных данных
    void drawSurface(SurfData* surfData, int angle) const;
    void drawBand(BandData* bandData, int buildType, bool uhf, int angle) const;
    void drawDataIsolines(std::vector<MarchingSquares::levelPaths> result,
                            double* hslA, double* hslB, const double* hslAStep, const double* hslBStep, const QVector<double>& oXTemp,
                            const QVector<double>& oYTemp, bool
                            shiftA, bool shiftB, int hslABorder, int hslBBorder, int angle, double stepX, double stepY) const;
    void drawDataLines(QList<UniversalLines>* Trajgrad, int index, int angle) const;
};

#endif // BASICGRAPH_H
