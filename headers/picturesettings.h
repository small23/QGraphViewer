// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#ifndef PICTURESETTINGS_H
#define PICTURESETTINGS_H

//Класс формы с настройками изображения

#include <QDialog>
#include "plotparameters.h"
#include "settingskeeper.h"
#include "constantsandstrings.h"

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
    void resetQuality() const;
    void resetScale() const;
    void resetScaleT() const;

private:
    Ui::PictureSettings *ui;
    PlotParameters *params;
    SettingsKeeper* settings;
    
#ifdef OWN_HIGHDPI_SCALE
    void resizeUi(qreal mratio);
    void getOriginFrames();
    void resizeEvent(QResizeEvent* event) override;

    struct widgetParams
    {
        QRect geom;
        QPoint pos;
        QSize minSize;
        QSize maxSize;
    };
    QVector<widgetParams*> windgetPramsList;
    QHash<QString, int> hashWidgets;
    int sizeH;
    int sizeW;
#endif
};

#endif // PICTURESETTINGS_H
