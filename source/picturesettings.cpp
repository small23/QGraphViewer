// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "picturesettings.h"
#include "ui_picturesettings.h"

PictureSettings::PictureSettings(PlotParameters* params, SettingsKeeper* settings,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PictureSettings)
{
    ui->setupUi(this);
    QTranslator qtTranslator;
    qtTranslator.load(settings->lang, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    QApplication::installTranslator(&qtTranslator);
    this->settings = settings;
    this->setWindowTitle(STR_Window_Settings);

#ifdef OWN_HIGHDPI_SCALE
    getOriginFrames();
#endif

    connect(ui->okButton,     SIGNAL(clicked()), this, SLOT(okButtonPushed()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonPushed()));
    connect(ui->resetQualityButton,     SIGNAL(clicked()), this, SLOT(resetQuality()));
    connect(ui->resetScaleButton, SIGNAL(clicked()), this, SLOT(resetScale()));
    connect(ui->resetScaleTButton, SIGNAL(clicked()), this, SLOT(resetScaleT()));
    this->params=params;
    ui->scaleSlider->setValue(static_cast<int>(params->drawScale));
    ui->qualitySlider->setValue(params->drawQuality);
    ui->scaleSliderT->setValue(params->drawRes / 100);
    switch (params->preferFormat) {
    case 0:
        ui->pngRadioButton->setChecked(true);
        break;
    case 1:
        ui->jpgRadioButton->setChecked(true);
        break;
    case 2:
        ui->bmpRadioButton->setChecked(true);
        break;
    case 3:
        ui->pdfRadioButton->setChecked(true);
        break;
    default:
        ui->pngRadioButton->setChecked(true);
        break;
    }
}

void PictureSettings::resetQuality() const
{
    ui->qualitySlider->setValue(90);
}

void PictureSettings::resetScale() const
{
    ui->scaleSlider->setValue(6);
}

void PictureSettings::resetScaleT() const
{
    ui->scaleSliderT->setValue(6);
}

void PictureSettings::okButtonPushed()
{
    params->drawScale=ui->scaleSlider->value();
    params->drawQuality=ui->qualitySlider->value();
    params->drawRes = ui->scaleSliderT->value() * 100;
    if (ui->pngRadioButton->isChecked())
        params->preferFormat=0;
    else if (ui->jpgRadioButton->isChecked())
        params->preferFormat=1;
    else if (ui->bmpRadioButton->isChecked())
        params->preferFormat=2;
    else if (ui->pdfRadioButton->isChecked())
        params->preferFormat = 3;
    else
        params->preferFormat=0;
    settings->updateDrawParams(params);
    this->close();
}
void PictureSettings::cancelButtonPushed()
{
    this->close();
}

#ifdef OWN_HIGHDPI_SCALE

void PictureSettings::resizeUi(qreal mratio)
{
#ifdef DEBUG_PAINT
    QString wName = "";
    int counter = 0;
#endif
    QString widgetClass;
    QString widgetName;
    widgetParams* params;
    foreach(QWidget * w, this->findChildren<QWidget*>())
    {
        widgetClass = w->metaObject()->className();
        widgetName = w->objectName();

        if (widgetClass == "QWidget" || widgetName.count() == 0 || widgetName.contains("qt_")) // Skip all non-user elements
            continue;

        int i = hashWidgets.value(w->objectName());
        if (i > 0)
        {
            params = windgetPramsList[i - 1];
            QPoint pos = params->pos * mratio;

            w->resize(params->geom.width() * mratio, params->geom.height() * mratio);
            w->move(pos);
#ifdef DEBUG_PAINT
            counter++;
            w->update();
            w->repaint();
            QApplication::processEvents();
#endif
        }
    }
}

void PictureSettings::getOriginFrames()
{
    QString widgetClass;
    QString widgetName;
    widgetParams* params;
    foreach(QWidget * w, this->findChildren<QWidget*>())
    {
        widgetClass = w->metaObject()->className();
        widgetName = w->objectName();
        if (widgetClass == "QWidget" || widgetName.count() == 0 || widgetName.contains("qt_")) // Skip all non-user elements
            continue;
        widgetParams* params = new widgetParams();
        params->pos = w->pos();
        params->geom = w->geometry();
        params->minSize = w->minimumSize();
        params->maxSize = w->maximumSize();
        windgetPramsList.append(params);
        hashWidgets.insert(w->objectName(), windgetPramsList.count());
    }
    sizeH = this->height();
    sizeW = this->width();
}

void PictureSettings::resizeEvent(QResizeEvent* event)
{
    QScreen* screen = QGuiApplication::screenAt(this->mapToGlobal({ this->width() / 2,this->height() / 2 }));
    qreal scale = screen->logicalDotsPerInch() / 96.0;
    if (this->maximumSize().height() > sizeH * scale)
    {
        this->setMinimumSize(sizeW * scale, sizeH * scale);
        this->resize(sizeW * scale, sizeH * scale);
        this->setMaximumSize(sizeW * scale, sizeH * scale);
    }
    else
    {
        this->setMaximumSize(sizeW * scale, sizeH * scale);
        this->resize(sizeW * scale, sizeH * scale);
        this->setMinimumSize(sizeW * scale, sizeH * scale);
    }
    resizeUi(scale);
}
#endif


PictureSettings::~PictureSettings()
{
    delete ui;
}

