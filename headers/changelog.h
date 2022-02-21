// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#ifndef CHANGELOG_H
#define CHANGELOG_H

#include <QDialog>
#include "constantsandstrings.h"
#include "ui_changelog.h"
#include "QTranslator"
#include "QLibraryInfo"
#include "settingskeeper.h"
#include <QGuiApplication>

namespace Ui {
class changelog;
}

class changelog : public QDialog
{
    Q_OBJECT

public:
    explicit changelog(SettingsKeeper *settings,QWidget *parent = nullptr);
    ~changelog();

private slots:
    void cancelButtonPushed();
    void showEvent(QShowEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;

private:
    Ui::changelog *ui;
    QPixmap appLogo;
#ifdef OWN_HIGHDPI_SCALE
    void resizeUi(qreal mratio);
    void getOriginFrames();

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

#endif // CHANGELOG_H
