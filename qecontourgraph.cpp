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
    customPlot->show();
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
        drawDataIsolines(result, &hslA, &hslB, &hslAStep,
            &hslBStep, surfData->oX, surfData->oY, shiftA, shiftB,
            colorDelimiterA, colorDelimiterB, plotParams->tab5surfaceRotate*90, surfData->oX.at(1) - surfData->oX.at(0),
            surfData->oY.at(1) - surfData->oY.at(0));

    delete contour;
}

void QEContourGraph::drawDataIsolines(std::vector<MarchingSquares::levelPaths> result,
    double* hslA, double* hslB, const double* hslAStep, const double* hslBStep, const QVector<double>& oXTemp, const QVector<double>
    & oYTemp, bool shiftA, bool shiftB,
    int hslABorder, int hslBBorder, int angle, double stepX, double stepY) const
{
    QPen pen;

    int hslAChange = 0;
    int hslBChange = 0;

    pen.setStyle(Qt::PenStyle::SolidLine);
    pen.setColor(QColor(0, 0, 0));
    pen.setWidthF(plotParams->tab5surfaceWidth);

    QCPCurve* newCurve1;
    QCPCurve* newCurve2;
    newCurve1 = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
    newCurve2 = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
    pen.setStyle(Qt::PenStyle::SolidLine);
    newCurve1->setPen(pen);
    pen.setStyle(Qt::PenStyle::DashLine);
    newCurve2->setPen(pen);
    for (uint i = 0; i < result.size(); i++)
    {
        if (i % 2 == 0)
        {
            if (plotParams->tab5ColorContours)
            {
                pen.setStyle(Qt::PenStyle::SolidLine);
                QColor temp;
                temp.setHsv(static_cast<int>(*hslB), 255, 255);
                pen.setColor(temp);
                newCurve1->setPen(pen);
            }
        }
        else
        {
            if (plotParams->tab5ColorContours)
            {
                pen.setStyle(Qt::PenStyle::DashLine);
                QColor temp;
                temp.setHsv(static_cast<int>(*hslA), 255, 255);
                pen.setColor(temp);
                newCurve2->setPen(pen);
            }
        }

        for (uint ii = 0; ii < result[i].size(); ii++)
        {
            if (result[i][ii].size() > 4)
            {
                if (i % 2 == 0)
                {
                    for (int iii = 0; iii < result[i][ii].size(); iii++)
                    {

                        qreal x = result[i][ii][iii].x();
                        qreal y = result[i][ii][iii].y();
                        if (x >= oXTemp.at(1) && y >= oYTemp.at(1) && x <= oXTemp.at(oXTemp.count() - 1) && y <= oYTemp.at(oYTemp.count() - 1))
                        {
                            x -= stepX / 2;
                            y -= stepY / 2;
                            switch (angle)
                            {
                            case 0: case 180:
                                newCurve1->addData(x, y);
                                break;
                            case 90: case 270:
                                newCurve1->addData(y, x);
                                break;
                            default:
                                break;
                            }
                            //newCurve1->addData(x, y);
                        }
                        else
                            newCurve1->addData(qQNaN(), qQNaN());
                    }
                    newCurve1->addData(qQNaN(), qQNaN());
                }
                else
                {
                    for (int iii = 0; iii < result[i][ii].size(); iii++)
                    {

                        qreal x = result[i][ii][iii].x();
                        qreal y = result[i][ii][iii].y();
                        if (x >= oXTemp.at(1) && y >= oYTemp.at(1) && x <= oXTemp.at(oXTemp.count() - 1) && y <= oYTemp.at(oYTemp.count() - 1))
                        {
                            x -= stepX / 2;
                            y -= stepY / 2;
                            switch (angle)
                            {
                            case 0: case 180:
                                newCurve2->addData(x, y);
                                break;
                            case 90: case 270:
                                newCurve2->addData(y, x);
                                break;
                            default:
                                break;
                            }
                            //newCurve2->addData(x, y);
                        }
                        else
                            newCurve2->addData(qQNaN(), qQNaN());
                    }
                    newCurve2->addData(qQNaN(), qQNaN());
                }
            }
        }
        if (plotParams->tab5ColorContours)
        {
            if (i % 2 == 0)
            {
                if (!result[i].empty())
                {
                    hslBChange++;
                    if (shiftB)
                    {
                        if (hslBChange > 3)
                            *hslB += *hslBStep;
                    }
                    else
                        *hslB += *hslBStep;
                }
                if (newCurve1->data()->size() != 0)
                    newCurve1 = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
                else
                {
                    customPlot->removePlottable(newCurve1);
                    newCurve1 = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
                }
            }
            else
            {
                if (newCurve2->data()->size() != 0)
                    newCurve2 = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
                else
                {
                    customPlot->removePlottable(newCurve2);
                    newCurve2 = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
                }
                if (!result[i].empty())
                {
                    hslAChange++;
                    if (shiftA)
                    {
                        if (hslAChange > 3)
                            *hslA += *hslAStep;
                    }
                    else
                        *hslA += *hslAStep;
                }

            }
        }
    }
    if (newCurve1->data()->size() == 0)
    {
        customPlot->removePlottable(newCurve1);
    }
    if (newCurve2->data()->size() == 0)
    {
        customPlot->removePlottable(newCurve2);
    }
}
