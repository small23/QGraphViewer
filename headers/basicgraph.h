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
    void drawDataLines(QList<UniversalLines>* Trajgrad, int index, int angle) const;
};

#endif // BASICGRAPH_H
