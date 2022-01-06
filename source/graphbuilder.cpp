#include "graphbuilder.h"

GraphBuilder::GraphBuilder(SettingsKeeper* settings, const QString& title, PlotParameters* plotParams, const QFont& font, QWidget* parent) :
	settings(settings), parent(parent), customPlot(new QCustomPlot()), plotParams(plotParams), font(font)
{
	customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
    connect(customPlot, SIGNAL(destroyed(QObject*)), this, SLOT(deletionOnClose(QObject*)));
    connect(customPlot, SIGNAL(resizeEvent(QResizeEvent*)), this, SLOT(resizeEvent(QResizeEvent*)));
    customPlot->setWindowTitle(title);
    customPlot->setAttribute(Qt::WA_DeleteOnClose);

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
    
}

void GraphBuilder::draw(){

}

void GraphBuilder::deletionOnClose(QObject* obj)
{
    this->deleteLater();
}

void GraphBuilder::contextMenuRequest(const QPoint pos)
{
    QMenu* menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);
    menu->addAction(STR_Graph_SaveGraph, this, SLOT(savePicture()));
    menu->addAction(STR_Graph_Settings, parent, SLOT(showPictureSettings()));
    menu->popup(customPlot->mapToGlobal(pos));
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
