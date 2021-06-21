#include "changelog.h"
#include "ui_changelog.h"

changelog::changelog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::changelog)
{
    ui->setupUi(this);
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
