// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "filedialogsload.h"

 FileDialogsLoad::FileDialogsLoad(Ui::MainWindow *uiInt,QWidget *parentInt, SettingsKeeper* settings)
{
    ui=uiInt;
    parent=parentInt;
    this->settings = settings;
}

void FileDialogsLoad::fileDialogMolTrajP2Load()
{
    QList<QString> fileNames = QFileDialog::getOpenFileNames(this,
        STR_Dialog_OpenFile, settings->lastPath,
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
        else
            QMessageBox::warning(this, STR_ErrorTitle_AddingError, STR_ErrorMessage_NonStandartNameMessage.arg(fileInfo.fileName()));

        settings->updatePath(fileInfo.absolutePath());
    }
}

void FileDialogsLoad::loadFileButtonCliked(const int id)
{
    QString fileName;
    if (id==5)
        fileName = QFileDialog::getOpenFileName(this,
            STR_Dialog_OpenFile, settings->lastPath,
                "Main files (*.outp);;All Files (*)");
    else
        fileName = QFileDialog::getOpenFileName(this,
            STR_Dialog_OpenFile, settings->lastPath,
                "f25 files (*.f25);;All Files (*)");


    if (fileName!="")
    {
	    const QFileInfo fileinfo(fileName);
        settings->updatePath(fileinfo.absolutePath());
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
