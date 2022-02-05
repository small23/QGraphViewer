// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "graphbuilder.h"

GraphBuilder::GraphBuilder(SettingsKeeper* settings, const QString& title, PlotParameters* plotParams, const QFont& font, QWidget* parent) :
	settings(settings), parent(parent), customPlot(new QCustomPlot()), plotParams(plotParams), font(font)
{
	//customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    this->setContextMenuPolicy(Qt::CustomContextMenu);
	//connect(customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
	connect(this, SIGNAL(destroyed(QObject*)), this, SLOT(deletionOnClose(QObject*)));
    this->setWindowTitle(title);
    this->setAttribute(Qt::WA_DeleteOnClose);

    customPlot->xAxis2->setVisible(true);
    customPlot->yAxis2->setVisible(true);
    customPlot->xAxis2->setTicks(false);
    customPlot->yAxis2->setTicks(false);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setTickLabels(false);

    customPlot->setFont(font);
    customPlot->xAxis->setTickLabelFont(font);
    customPlot->yAxis->setTickLabelFont(font);
    customPlot->xAxis->setLabelFont(font);
    customPlot->yAxis->setLabelFont(font);

    customPlot->setBufferDevicePixelRatio(plotParams->displayScale);

    imageOnWidget.setParent(this);
    imageOnWidget.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    this->setMinimumSize(250, 250);

    vbl = new QVBoxLayout(this);
    vbl->addWidget(&imageOnWidget);
    vbl->setContentsMargins(0, 0, 0, 0);
    QPalette Pal(palette());

    Pal.setColor(QPalette::Background, Qt::white);
	this->setAutoFillBackground(true);
	this->setPalette(Pal);
    
}

void GraphBuilder::draw(){

}



void GraphBuilder::deletionOnClose(QObject* obj)
{
    this->deleteLater();
}

void GraphBuilder::resizeEvent(QResizeEvent* event)
{
    if (!plotDraw.isNull())
    {
        float thisAspectRatio =  event->size().height() / (float)event->size().width();
        int width, height;
        if (thisAspectRatio > compareScale)
        {
            width = event->size().width();
            height = width * compareScale;
        }
        else
        {
            height = event->size().height();
            width = height / compareScale;
        }
        plotDraw.setDevicePixelRatio(this->devicePixelRatioF());
        imageOnWidget.setPixmap(plotDraw.scaled(width * this->devicePixelRatioF(), height * this->devicePixelRatioF(),
            Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }
	QWidget::resizeEvent(event);
}

void GraphBuilder::showEvent(QShowEvent* event)
{
    plotWidth = customPlot->minimumWidth();
    plotHeight = customPlot->minimumHeight();
    plotDraw = customPlot->toPixmap(plotWidth, plotHeight, 3 * this->devicePixelRatioF());
    plotDraw.setDevicePixelRatio(this->devicePixelRatioF());
    this->resize(plotWidth, plotHeight);
	QWidget::showEvent(event);
    QApplication::processEvents();
}

void GraphBuilder::closeEvent(QCloseEvent* event)
{
	QWidget::closeEvent(event);
    delete customPlot;
    delete vbl;
}

void GraphBuilder::contextMenuRequest(const QPoint pos)
{
    QMenu* menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    menu->addAction(STR_Graph_SaveGraph, this, SLOT(savePicture()));
    menu->addAction(STR_Graph_Settings, parent, SLOT(showPictureSettings()));
    menu->popup(this->mapToGlobal(pos));
}

void GraphBuilder::savePicture()
{
    QString filenameOnly = "";
    auto fileFormats ="PNG file (*.png);;All Files (*)";
    switch (plotParams->preferFormat)
    {
    case 0:
        filenameOnly = customPlot->windowTitle() + ".png";
        fileFormats = "PNG file (*.png);;All Files (*)";
        break;
    case 1:
        filenameOnly = customPlot->windowTitle() + ".jpg";
        fileFormats = "JPG file (*.jpg);;All Files (*)";
        break;
    case 2:
        filenameOnly = customPlot->windowTitle() + ".bmp";
        fileFormats = "BMP file (*.bmp);All Files (*)";
        break;
    case 3:
        filenameOnly = customPlot->windowTitle() + ".pdf";
        fileFormats = "PDF Vector file (*.pdf);All Files (*)";
        break;
    default:
        break;
    }

    const QString fileName = QFileDialog::getSaveFileName(this,
        STR_Graph_SaveGraph, settings->lastPath + filenameOnly,
                                                          fileFormats);
    if (fileName != "")
    {
        const double h = static_cast<double>(customPlot->height());
        const double w = static_cast<double>(customPlot->width());
        const double scale = plotParams->drawScale / (h > w ? h / static_cast<double>(GRAPH_SCALE) : w / static_cast<double>(GRAPH_SCALE)) / 2;
        bool success = false;

    	switch (plotParams->preferFormat)
        {
        case 0:
            success = customPlot->savePng(fileName, customPlot->width(), customPlot->height(), scale);
            break;
        case 1:
            success = customPlot->saveJpg(fileName, customPlot->width(), customPlot->height(), scale, plotParams->drawQuality);
            break;
        case 2:
            success = customPlot->saveBmp(fileName, customPlot->width(), customPlot->height(), scale);
            break;
        case 3:
            success = customPlot->savePdf(fileName, customPlot->width(), customPlot->height(), QCP::epNoCosmetic);
            break;
        default:
            break;
        }


        const QFileInfo fileinfo(fileName);
        settings->updatePath(fileinfo.absolutePath());
        if (success == false)
        {
            QMessageBox::critical(this, STR_ErrorTitle_SaveError, STR_ErrorMessage_ImageSavingError);
        }
    }
}

void GraphBuilder::drawDataIsolines(std::vector<MarchingSquares::levelPaths> result,
    double* hslA, double* hslB, const double* hslAStep, const double* hslBStep, const QVector<double>& oXTemp, const QVector<double>& oYTemp,
    bool shiftA, bool shiftB,
    int angle, double stepX, double stepY,
    double surfaceWidth, bool colorLines) const
{
    QPen pen;

    int hslAChange = 0;
    int hslBChange = 0;

    pen.setStyle(Qt::PenStyle::SolidLine);
    pen.setColor(QColor(0, 0, 0));
    pen.setWidthF(surfaceWidth);

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
            if (colorLines)
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
            if (colorLines)
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
        if (colorLines)
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