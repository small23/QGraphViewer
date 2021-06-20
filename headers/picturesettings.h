#ifndef PICTURESETTINGS_H
#define PICTURESETTINGS_H

//Класс формы с настройками изображения

#include <QDialog>
#include "plotparameters.h"
#include "SettingsKeeper.h"

namespace Ui {
class PictureSettings;
}

class PictureSettings : public QDialog
{
    Q_OBJECT

public:
    explicit PictureSettings(PlotParameters *params,SettingsKeeper* settings,QWidget *parent = nullptr);
    ~PictureSettings();

private slots:
    void okButtonPushed();
    void cancelButtonPushed();
    void resetQuality();
    void resetScale();

private:
    Ui::PictureSettings *ui;
    PlotParameters *params;
    SettingsKeeper* settings;
};

#endif // PICTURESETTINGS_H
