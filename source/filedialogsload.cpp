#include "filedialogsload.h"
#include "ui_mainwindow.h"

 FileDialogsLoad::FileDialogsLoad(Ui::MainWindow *uiInt,QWidget *parentInt, SettingsKeeper* settings)
{
    ui=uiInt;
    parent=parentInt;
    this->settings = settings;
}

void FileDialogsLoad::FileDialogMolTrajP2Load()
{
    QList<QString> fileNames = QFileDialog::getOpenFileNames(this,
            tr("Open file"), settings->lastPath,
            tr("Plot files (*.dat);;All Files (*)"));
    for(int i=0; i<fileNames.count(); i++)
    {
        QFileInfo fileInfo(fileNames[i]);

        if (fileInfo.fileName().toUpper().contains("TRAJGRAD.DAT"))
            ui->tab1FileLine1->setText(fileNames[i]);
        else if (fileInfo.fileName().toUpper().contains("MOLGRAPH"))
            ui->tab1FileLine2->setText(fileNames[i]);
        else if (fileInfo.fileName().toUpper().contains("P2DCRYIN"))
            ui->tab1FileLine3->setText(fileNames[i]);
        else if (fileInfo.fileName().toUpper().contains("SURFELFB"))
            ui->tab1FileLine4->setText(fileNames[i]);
        else if (fileInfo.fileName().toUpper().contains("SURFGKIN"))
            ui->tab1FileLine4->setText(fileNames[i]);
        else if (fileInfo.fileName().toUpper().contains("SURFGRHO"))
            ui->tab1FileLine4->setText(fileNames[i]);
        else if (fileInfo.fileName().toUpper().contains("SURFKKIN"))
            ui->tab1FileLine4->setText(fileNames[i]);
        else if (fileInfo.fileName().toUpper().contains("SURFLAPM"))
            ui->tab1FileLine4->setText(fileNames[i]);
        else if (fileInfo.fileName().toUpper().contains("SURFLAPP"))
            ui->tab1FileLine4->setText(fileNames[i]);
        else if (fileInfo.fileName().toUpper().contains("SURFRHOO"))
            ui->tab1FileLine4->setText(fileNames[i]);
        else if (fileInfo.fileName().toUpper().contains("SURFSPDE"))
            ui->tab1FileLine4->setText(fileNames[i]);
        else if (fileInfo.fileName().toUpper().contains("SURFVIRI"))
            ui->tab1FileLine4->setText(fileNames[i]);
        else if (fileInfo.fileName().toUpper().contains("SURFELFB"))
            ui->tab1FileLine4->setText(fileNames[i]);
        else
            QMessageBox::warning(this, tr("Ошибка добавления"), tr("Файл '") + fileInfo.fileName() + tr("' имеет нестандартное имя и не будет добавлен."));

        settings->UpdatePath(fileInfo.absolutePath());
        /*
    	QList<QString> temp = fileNames[i].split("/");
        if (temp[temp.count()-1].toUpper().contains("TRAJGRAD.DAT"))
            ui->tab1FileLine1->setText(fileNames[i]);
        else if (temp[temp.count()-1].toUpper().contains("MOLGRAPH"))
            ui->tab1FileLine2->setText(fileNames[i]);
        else if (temp[temp.count()-1].toUpper().contains("P2DCRYIN"))
            ui->tab1FileLine3->setText(fileNames[i]);
        else if (temp[temp.count()-1].toUpper().contains("SURFELFB"))
            ui->tab1FileLine4->setText(fileNames[i]);
        else if (temp[temp.count()-1].toUpper().contains("SURFGKIN"))
            ui->tab1FileLine4->setText(fileNames[i]);
        else if (temp[temp.count()-1].toUpper().contains("SURFGRHO"))
            ui->tab1FileLine4->setText(fileNames[i]);
        else if (temp[temp.count()-1].toUpper().contains("SURFKKIN"))
            ui->tab1FileLine4->setText(fileNames[i]);
        else if (temp[temp.count()-1].toUpper().contains("SURFLAPM"))
            ui->tab1FileLine4->setText(fileNames[i]);
        else if (temp[temp.count()-1].toUpper().contains("SURFLAPP"))
            ui->tab1FileLine4->setText(fileNames[i]);
        else if (temp[temp.count()-1].toUpper().contains("SURFRHOO"))
            ui->tab1FileLine4->setText(fileNames[i]);
        else if (temp[temp.count()-1].toUpper().contains("SURFSPDE"))
            ui->tab1FileLine4->setText(fileNames[i]);
        else if (temp[temp.count()-1].toUpper().contains("SURFVIRI"))
            ui->tab1FileLine4->setText(fileNames[i]);
        else if (temp[temp.count()-1].toUpper().contains("SURFELFB"))
            ui->tab1FileLine4->setText(fileNames[i]);
        else
            QMessageBox::warning(this,"Ошибка добавления","Файл '" + temp[temp.count()-1] +"' имеет нестандартное имя и не будет добавлен.");
            */
    }
}

void FileDialogsLoad::LoadFileButtonCliked(int id)
{
    QString fileName;
    if (id==5)
        fileName = QFileDialog::getOpenFileName(this,
                tr("Open file"), settings->lastPath,
                tr("Main files (*.outp);;All Files (*)"));
    else
        fileName = QFileDialog::getOpenFileName(this,
                tr("Open file"), settings->lastPath,
                tr("f25 files (*.f25);;All Files (*)"));


    if (fileName!="")
    {
        QFileInfo fileinfo(fileName);
        settings->UpdatePath(fileinfo.absolutePath());
        QString lineName;
        if (id>6)
           lineName = QString("tab2FileLine%1").arg(id-6);
        else
            lineName = QString("tab1FileLine%1").arg(id);

        QLineEdit* lineEdit = parent->findChild<QLineEdit*>(lineName);
        if (lineEdit != nullptr)
            lineEdit->setText(fileName);
    }
}
