// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#ifndef CHANGELOG_H
#define CHANGELOG_H

#include <QDialog>
#include "constantsandstrings.h"
#include "ui_changelog.h"
#include "QTranslator"
#include "QLibraryInfo"
#include "settingsKeeper.h"

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

private:
    Ui::changelog *ui;
};

#endif // CHANGELOG_H
