#include "changelog.h"
#include "ui_changelog.h"
#include "QTranslator"
#include "QLibraryInfo"

changelog::changelog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changelog)
{
    ui->setupUi(this);
    QTranslator qtTranslator;
    qtTranslator.load("qt_en", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    QApplication::installTranslator(&qtTranslator);
    const QPixmap pixmap2(":logos/Logos/logo.ico");
    ui->logo->setPixmap(pixmap2);
    this->setWindowTitle(tr("Список изменений"));
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(cancelButtonPushed()));
}

void changelog::cancelButtonPushed()
{
    this->close();
}

changelog::~changelog()
{
    delete ui;
}
