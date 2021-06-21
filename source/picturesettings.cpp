#include "picturesettings.h"
#include "ui_picturesettings.h"

PictureSettings::PictureSettings(PlotParameters* params, SettingsKeeper* settings,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PictureSettings)
{
    ui->setupUi(this);
    this->settings = settings;
    this->setWindowTitle(tr("Настройки"));
	
    connect(ui->okButton,     SIGNAL(clicked()), this, SLOT(okButtonPushed()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(cancelButtonPushed()));
    connect(ui->resetQualityButton,     SIGNAL(clicked()), this, SLOT(resetQuality()));
    connect(ui->resetScaleButton, SIGNAL(clicked()), this, SLOT(resetScale()));
    this->params=params;
    ui->scaleSlider->setValue(static_cast<int>(params->drawScale));
    ui->qualitySlider->setValue(params->drawQuality);
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

void PictureSettings::okButtonPushed()
{
    params->drawScale=ui->scaleSlider->value();
    params->drawQuality=ui->qualitySlider->value();
    if (ui->pngRadioButton->isChecked())
        params->preferFormat=0;
    else if (ui->jpgRadioButton->isChecked())
        params->preferFormat=1;
    else if (ui->bmpRadioButton->isChecked())
        params->preferFormat=2;
    else
        params->preferFormat=0;
    settings->updateDrawParams(params);
    this->close();
}
void PictureSettings::cancelButtonPushed()
{
    this->close();
}


PictureSettings::~PictureSettings()
{
    delete ui;
}

