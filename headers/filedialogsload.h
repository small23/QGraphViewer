// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#ifndef FILEDIALOGSLOAD_H
#define FILEDIALOGSLOAD_H

//Класс обработки вызова окна загрузки данных через ФМ
//Раскладывает файлы по полям на форме,
//проверяет корректность расширений

#include <QWidget>
#include "ui_mainwindow.h"
#include "QFileDialog"
#include "QMessageBox"
#include "settingskeeper.h"
#include "constantsandstrings.h"
#include "ui_mainwindow.h"

class FileDialogsLoad : public QWidget
{
    Q_OBJECT
public:
    //Конструктор класса, передается ссылка на UI и адрес родительского окна
    explicit FileDialogsLoad(Ui::MainWindow *ui, QWidget *parent, SettingsKeeper* settings);
private:
    Ui::MainWindow *ui;
    QWidget *parent;
    SettingsKeeper* settings;
public slots:
    //Публичные слоты для вызова из под MainWindow
    //Слот обработки кнопки загрузки данных MOLGRAPH\TRAJGRAD
    void fileDialogMolTrajP2Load();
    //Обработчик остальных кнопок загрузки в остальных участках форм
    //ID - идентификатор кнопки
    void loadFileButtonCliked(int id);

};

#endif // FILEDIALOGSLOAD_H
