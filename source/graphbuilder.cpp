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

    imageOnWidget.setParent(this);
    //imageOnWidget =  QLabel("Start", this);
    imageOnWidget.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    this->setMinimumSize(250, 250);

    QPushButton Bu_Quit("Quit", this);
    QObject::connect(&Bu_Quit, SIGNAL(clicked()), qApp, SLOT(quit()));

    QVBoxLayout* vbl = new QVBoxLayout(this);
    vbl->addWidget(&imageOnWidget);
    vbl->addWidget(&Bu_Quit);
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
    float thisAspectRatio = (float)event->size().width() / event->size().height();
    int width, height;
    if (thisAspectRatio > aspectRatio)
    {
        height = event->size().height();
        width = height * aspectRatio;
    }
    else
    {
        width = event->size().width();
        height = width / aspectRatio;
    }
    imageOnWidget.setPixmap(plotDraw.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation));
	QWidget::resizeEvent(event);
}

void GraphBuilder::showEvent(QShowEvent* event)
{
    plotWidth = customPlot->minimumWidth();
    plotHeight = customPlot->minimumHeight();
    plotDraw = customPlot->toPixmap(plotWidth, plotHeight, 1.5);
    this->resize(plotWidth, plotHeight);
	QWidget::showEvent(event);
    plotDraw = customPlot->toPixmap(plotWidth, plotHeight, 5);
}

void GraphBuilder::closeEvent(QCloseEvent* event)
{
	QWidget::closeEvent(event);
    delete customPlot;
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
