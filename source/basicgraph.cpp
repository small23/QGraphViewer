#include "basicgraph.h"

BasicGraph::BasicGraph(SettingsKeeper* settings, const QString& title, PlotParameters* plotParams, const QFont font, QWidget* parent)
: GraphBuilder(settings, title, plotParams, font, parent)
{
    plotType = 1;
}

void BasicGraph::draw(const bool hideAxis, const int buildType, const bool uhf, GraphicsData* graphics,
                      SurfData* surfaceData, BandData* bandData, const int angle)
{
    QCPCurve* newCurve;
    QPen pen;
    if (plotParams->tab1PlotParams[6].show)
    {
        if (surfaceData->oF.count() != 0)
            drawSurface(surfaceData, angle);
        if (bandData->outputMAPN.count() != 0)
            drawBand(bandData, buildType, uhf, angle);
    }

    drawDataLines(graphics->Trajgrad, 0, angle);
    drawDataLines(graphics->MolgraphConn, 3, angle);
    drawDataLines(graphics->MolgraphBass1, 1, angle);
    drawDataLines(graphics->MolgraphBass2, 2, angle);

    pen.setColor(plotParams->tab1PlotParams[4].color);
    pen.setWidthF(plotParams->tab1PlotParams[4].width);
    if (plotParams->tab1PlotParams[4].show == true)
    {
        newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
        for (int i = 0; i < graphics->MolgraphPoints->count(); i++)
        {
            switch (angle)
            {
            case 0: case 180:
                newCurve->addData(graphics->MolgraphPoints->at(i).x, graphics->MolgraphPoints->at(i).y);
                break;
            case 90: case 270:
                newCurve->addData(graphics->MolgraphPoints->at(i).y, graphics->MolgraphPoints->at(i).x);
                break;
            default:
                break;
            }

        }
        newCurve->setLineStyle(QCPCurve::lsNone);
        newCurve->setPen(pen);
        newCurve->setScatterStyle(plotParams->tab1PlotParams[4].pointStyle);
    }


    if (graphics->Atoms->count() != 0 && plotParams->tab1PlotParams[5].show)
    {
        pen.setColor(plotParams->tab1PlotParams[5].color);
        pen.setWidthF(plotParams->tab1PlotParams[5].width);
        newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
        QVector<double> x;
        QVector<double> y;
        switch (angle)
        {
        case 0:
            x = graphics->Atoms->at(0).x;
            y = graphics->Atoms->at(0).y;
            break;
        case 90:
            for (int j = 0; j < graphics->Atoms->at(0).x.size(); j++)
                y.append(graphics->Atoms->at(0).x[j]);

            x = graphics->Atoms->at(0).y;
            break;

        case 180:
            for (int j = 0; j < graphics->Atoms->at(0).x.size(); j++)
                x.append(graphics->Atoms->at(0).x[j]);
            for (int j = 0; j < graphics->Atoms->at(0).y.size(); j++)
                y.append(graphics->Atoms->at(0).y[j]);
            break;
        case 270:
            for (int j = 0; j < graphics->Atoms->at(0).y.size(); j++)
                x.append(graphics->Atoms->at(0).y[j]);

            y = graphics->Atoms->at(0).x;
            break;
        default:
            break;
        }
        newCurve->setData(x, y);
        newCurve->setLineStyle(QCPCurve::lsNone);
        newCurve->setPen(pen);
        newCurve->setScatterStyle(plotParams->tab1PlotParams[5].pointStyle);
    }

    customPlot->xAxis->grid()->setVisible(false);
    customPlot->yAxis->grid()->setVisible(false);

    customPlot->xAxis->rescale(true);
    customPlot->yAxis->rescale(true);
    if (graphics->parsedFrameLoc == true)
    {
        switch (angle)
        {
        case 0: case 180:
            customPlot->xAxis->setRange(graphics->frameLoc[0], graphics->frameLoc[1]);
            customPlot->yAxis->setRange(graphics->frameLoc[2], graphics->frameLoc[3]);
            break;
        case 90: case 270:
            customPlot->yAxis->setRange(graphics->frameLoc[0], graphics->frameLoc[1]);
            customPlot->xAxis->setRange(graphics->frameLoc[2], graphics->frameLoc[3]);
            break;
        default:
            break;
        }
    }
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

    if (hideAxis == true)
    {
        customPlot->xAxis->setTicks(false);
        customPlot->xAxis->setTickLabels(false);
        customPlot->yAxis->setTicks(false);
        customPlot->yAxis->setTickLabels(false);
    }

    switch (angle)
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

void BasicGraph::drawDataLines(QList<UniversalLines>* data, const int index, const int angle) const
{
    QPen pen;
    pen.setStyle(plotParams->tab1PlotParams[index].style);
    pen.setColor(plotParams->tab1PlotParams[index].color);
    pen.setWidthF(plotParams->tab1PlotParams[index].width);
    QVector<double> x;
    QVector<double> y;
    if (plotParams->tab1PlotParams[0].show == true)
    {
        QCPCurve* newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
        for (int i = 0; i < data->count(); i++)
        {
            x.clear();
            y.clear();
            switch (angle)
            {
            case 0:
                x = data->at(i).x;
                y = data->at(i).y;
                break;
            case 90:
                for (int j = 0; j < data->at(i).x.size(); j++)
                    y.append(data->at(i).x[j]);

                x = data->at(i).y;
                break;

            case 180:
                for (int j = 0; j < data->at(i).x.size(); j++)
                    x.append(data->at(i).x[j]);
                for (int j = 0; j < data->at(i).y.size(); j++)
                    y.append(data->at(i).y[j]);
                break;
            case 270:
                for (int j = 0; j < data->at(i).y.size(); j++)
                    x.append(data->at(i).y[j]);

                y = data->at(i).x;
                break;
            default:
                break;
            }
            newCurve->addData(x, y);
            newCurve->addData(qQNaN(), qQNaN());
        }
        newCurve->setPen(pen);
    }
}

void BasicGraph::drawSurface(SurfData* surfData, const int angle) const
{

    QPen pen;

    pen.setStyle(Qt::PenStyle::SolidLine);
    pen.setColor(QColor(0, 0, 0));
    pen.setWidthF(plotParams->tab1surfaceWidth);

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

    while (plotParams->tab1surfacePrecision < tempLineParam)
    {
        lines.push_back(tempLineParam);
        lines.push_back(-tempLineParam);
        tempLineParam /= plotParams->tab1surfaceDivider;
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
                           colorDelimiterA, colorDelimiterB, angle, surfData->oX.at(1) - surfData->oX.at(0),
                           surfData->oY.at(1) - surfData->oY.at(0));

    delete contour;
}

void BasicGraph::drawBand(BandData* bandData, const int buildType, const bool uhf, const int angle) const
{
    QPen pen;

    pen.setStyle(Qt::PenStyle::SolidLine);
    pen.setColor(QColor(0, 0, 0));
    pen.setWidthF(plotParams->tab1surfaceWidth);

    std::vector<std::vector<double>> test;
    for (int i = 0; i < bandData->oYTempMapn.count(); i++)
    {
        std::vector<double> temp;
        for (int j = 0; j < bandData->oXTempMapn.count(); j++)
        {
            if (buildType == 0)
                temp.push_back(bandData->outputMAPN.at(0).at(j + bandData->oXTempMapn.count() * i));
            else if (buildType == 1)
                temp.push_back(bandData->outputMAPN.at(1).at(j + bandData->oXTempMapn.count() * i));
            else if (buildType == 2)
                temp.push_back(bandData->outputMAPN.at(2).at(j + bandData->oXTempMapn.count() * i));
            else if (buildType == 3)
                temp.push_back(bandData->outputMAPN.at(3).at(j + bandData->oXTempMapn.count() * i));
        }
        test.push_back(temp);
    }

    switch (buildType)
    {
    case 0:
        this->customPlot->setWindowTitle(STR_GraphTitle_PlotRo);
        break;
    case 1:
        if (uhf)
            this->customPlot->setWindowTitle(STR_GraphTitle_PlotSpin);
        else
            this->customPlot->setWindowTitle(STR_GraphTitle_PlotRoDef);
        break;
    case 2:
        this->customPlot->setWindowTitle(STR_GraphTitle_PlotRoDef);
        break;
    case 3:
        this->customPlot->setWindowTitle(STR_GraphTitle_PlotSpinDef);
        break;
    default:
        break;
    }

    MarchingSquares* contour = new MarchingSquares(test, bandData->oXTempMapn.at(0),
        bandData->oXTempMapn.at(bandData->oXTempMapn.count() - 1), bandData->oYTempMapn.at(0),
        bandData->oYTempMapn.at(bandData->oYTempMapn.count() - 1));
    std::vector<double> lines;
    double tempLineParam = 100;
    int colorDelimiter = 0;
    double hslA = 270;
    double hslB = 0;

    while (plotParams->tab1surfacePrecision < tempLineParam)
    {
        colorDelimiter++;
        lines.push_back(tempLineParam);
        lines.push_back(-tempLineParam);
        tempLineParam /= plotParams->tab1surfaceDivider;
    }
    double hslBStep;
    double hslAStep;

    lines.push_back(0);
    std::vector<MarchingSquares::levelPaths> result = contour->mkIsos(lines);

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
        hslBStep = 135.0 / (colorDelimiterB - 3);
        colorDelimiterB -= 3;
        shiftB = true;
    }
    else
        hslBStep = 135.0 / (colorDelimiterB - 0);

    int colorDelimiterA = 0;

    for (size_t i = 1; i < result.size(); i += 2)
    {
        if (!result[i].empty())
            colorDelimiterA++;
    }
    if (colorDelimiterA > 8)
    {
        hslAStep = (135.0 - 270.0) / (colorDelimiterA - 3);
        colorDelimiterA -= 3;
        shiftA = true;
    }
    else
        hslAStep = (135.0 - 270.0) / (colorDelimiterA - 0);
    if (bandData->oYTempMapn.size()>1 && bandData->oXTempMapn.size() > 1)
        drawDataIsolines(result, &hslA, &hslB, &hslAStep, &hslBStep,
                           bandData->oXTempMapn, bandData->oYTempMapn, shiftA, shiftB,
                           colorDelimiterB, colorDelimiterA, angle, bandData->oXTempMapn.at(1)- bandData->oXTempMapn.at(0),
                           bandData->oYTempMapn.at(1) - bandData->oYTempMapn.at(0));

    delete contour;
}

void BasicGraph::drawDataIsolines(std::vector<MarchingSquares::levelPaths> result,
    double* hslA, double* hslB,const double* hslAStep, const double* hslBStep, const QVector<double>& oXTemp, const QVector<double>
    & oYTemp, bool shiftA, bool shiftB,
    int hslABorder, int hslBBorder, int angle, double stepX, double stepY) const
{
    QPen pen;

    int hslAChange = 0;
    int hslBChange = 0;

    pen.setStyle(Qt::PenStyle::SolidLine);
    pen.setColor(QColor(0, 0, 0));
    pen.setWidthF(plotParams->tab1surfaceWidth);

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
            if (plotParams->colorContours)
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
            if (plotParams->colorContours)
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
        if (plotParams->colorContours)
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
                if (newCurve1->data()->size()!=0)
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