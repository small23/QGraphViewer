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
    appLogo.load(":logos/Logos/icon.png");
    this->setWindowTitle(STR_Window_Changelog);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(cancelButtonPushed()));
}

void changelog::cancelButtonPushed()
{
    this->hide();
}

void changelog::showEvent(QShowEvent* event)
{
	QDialog::showEvent(event);
    appLogo.setDevicePixelRatio(this->window()->windowHandle()->devicePixelRatio());
    qreal scale = this->window()->windowHandle()->devicePixelRatio();
    QPixmap labelLogo = appLogo.scaled(ui->logo->width() * scale, ui->logo->height() * scale, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->logo->setPixmap(labelLogo);
}

void changelog::resizeEvent(QResizeEvent* event)
{
	QDialog::resizeEvent(event);
    appLogo.setDevicePixelRatio(this->window()->windowHandle()->devicePixelRatio());
    qreal scale = this->window()->windowHandle()->devicePixelRatio();
    QPixmap labelLogo = appLogo.scaled(ui->logo->width() * scale, ui->logo->height() * scale, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    ui->logo->setPixmap(labelLogo);
}

changelog::~changelog()
{
    delete ui;
}
