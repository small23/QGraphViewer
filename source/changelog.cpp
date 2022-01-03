// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "changelog.h"

changelog::changelog(SettingsKeeper *settings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changelog)
{
    ui->setupUi(this);
    QTranslator qtTranslator;
    qtTranslator.load(settings->lang, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    QApplication::installTranslator(&qtTranslator);
    const QPixmap pixmap2(":logos/Logos/logo.ico");
    ui->logo->setPixmap(pixmap2);
    this->setWindowTitle(STR_Window_Changelog);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(cancelButtonPushed()));
}

void changelog::cancelButtonPushed()
{
    this->hide();
}

changelog::~changelog()
{
    delete ui;
}
