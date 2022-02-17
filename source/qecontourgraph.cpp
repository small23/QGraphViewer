#include "qecontourgraph.h"

QEContourGraph::QEContourGraph(SettingsKeeper* settings, const QString& title, PlotParameters* plotParams, QFont font, QWidget* parent)
	: GraphBuilder(settings, title, plotParams, font, parent)
{
	plotType = 1;
}

void QEContourGraph::draw(QeSurfData* data)
{
    drawSurface(data);

    QVector<double> tickValues;
    QVector<QString> tickLabels;

    customPlot->xAxis->grid()->setVisible(false);
    customPlot->yAxis->grid()->setVisible(false);

    customPlot->xAxis->rescale(true);
    customPlot->yAxis->rescale(true);

    const QCPRange xRange = customPlot->xAxis->range();
    const QCPRange yRange = customPlot->yAxis->range();
    compareScale = (yRange.upper - yRange.lower) / (xRange.upper - xRange.lower);
    if (compareScale < 1.01)
    {
        customPlot->setGeometry(30, 30, plotParams->drawRes, static_cast<int>(round(plotParams->drawRes * compareScale)));
        customPlot->setMinimumSize(plotParams->drawRes, static_cast<int>(round(plotParams->drawRes * compareScale)));
        customPlot->setMaximumSize(plotParams->drawRes, static_cast<int>(round(plotParams->drawRes * compareScale)));
    }
    else
    {
        customPlot->setGeometry(30, 30, static_cast<int>(round(plotParams->drawRes / compareScale)), plotParams->drawRes);
        customPlot->setMinimumSize(static_cast<int>(round(plotParams->drawRes / compareScale)), plotParams->drawRes);
        customPlot->setMaximumSize(static_cast<int>(round(plotParams->drawRes / compareScale)), plotParams->drawRes);
    }

    if (plotParams->tab5surfaceHideAxis == true)
    {
        customPlot->xAxis->setTicks(false);
        customPlot->xAxis->setTickLabels(false);
        customPlot->yAxis->setTicks(false);
        customPlot->yAxis->setTickLabels(false);
    }
    switch (plotParams->tab5surfaceRotate * 90)
    {
    case 0:
        customPlot->xAxis->setRangeReversed(false);
        customPlot->yAxis->setRangeReversed(false);
        break;
    case 90:
        customPlot->xAxis->setRangeReversed(false);
        customPlot->yAxis->setRangeReversed(true);
        break;
    case 180:
        customPlot->xAxis->setRangeReversed(true);
        customPlot->yAxis->setRangeReversed(true);
        break;
    case 270:
        customPlot->xAxis->setRangeReversed(true);
        customPlot->yAxis->setRangeReversed(false);
        break;
    default:
        break;
    }
    this->show();
}

void QEContourGraph::drawSurface(QeSurfData* surfData) const
{
    QPen pen;

    pen.setStyle(Qt::PenStyle::SolidLine);
    pen.setColor(QColor(0, 0, 0));
    pen.setWidthF(plotParams->tab5surfaceWidth); 

    std::vector<std::vector<double>> test;
    for (int i = 0; i < surfData->oY.count(); i++)
    {
        std::vector<double> temp;
        for (int j = 0; j < surfData->oX.count(); j++)
        {
            temp.push_back(surfData->oF.at(j + surfData->oX.count() * i));
        }
        test.push_back(temp);
    }
    MarchingSquares* contour = new MarchingSquares(test, surfData->oX.at(0),
        surfData->oX.at(surfData->oX.count() - 1), surfData->oY.at(0),
        surfData->oY.at(surfData->oY.count() - 1));
    std::vector<double> lines;
    double tempLineParam = 100;
    int colorDelimiter = 0;
    double hslA = 249;
    double hslB = 0;

    while (0.001 < tempLineParam)
    {
        lines.push_back(tempLineParam);
        lines.push_back(-tempLineParam);
        tempLineParam /= plotParams->tab5surfaceDivider;
        colorDelimiter++;
    }
    double hslBStep;
    double hslAStep;

    std::vector<MarchingSquares::levelPaths> result = contour->mkIsos(lines);

    int colorDelimiterA = 0;
    int colorDelimiterB = 0;
    for (size_t i = 0; i < result.size(); i += 2)
    {
        if (!result[i].empty())
            colorDelimiterB++;
    }
    bool shiftA = false;
    bool shiftB = false;
    if (colorDelimiterB > 8)
    {
        hslBStep = 135.0 / static_cast<double>(colorDelimiterB - 3);
        colorDelimiterB -= 3;
        shiftB = true;
    }
    else
        hslBStep = 135.0 / (colorDelimiterB - 0);

    for (size_t i = 1; i < result.size(); i += 2)
    {
        if (!result[i].empty())
            colorDelimiterA++;
    }
    if (colorDelimiterA > 8)
    {
        hslAStep = (135.0 - 270.0) / static_cast<double>(colorDelimiterA - 3);
        colorDelimiterA -= 3;
        shiftA = true;
    }
    else
        hslAStep = (135.0 - 270.0) / (colorDelimiterA - 0);
    if (surfData->oX.size() >= 2 && surfData->oY.size() >= 2)
    {
        drawDataIsolines(result, &hslA, &hslB, &hslAStep,
            &hslBStep, surfData->oX, surfData->oY, shiftA, shiftB,
            plotParams->tab5surfaceRotate * 90,
            surfData->oX.at(1) - surfData->oX.at(0), surfData->oY.at(1) - surfData->oY.at(0),
            plotParams->tab5surfaceWidth, plotParams->tab5ColorContours);
    }
       
    delete contour;
}
