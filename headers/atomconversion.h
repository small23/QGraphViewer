#ifndef ATOMCONVERSION_H
#define ATOMCONVERSION_H

//Класс конвертации координат атомов
//в различные системы координат
#include <QObject>
#include <QWidget>
#include "ui_mainwindow.h"
#include "Eigen/Eigen"
#include "QFile"
#include "QFileDialog"
#include "QTextStream"
#include "QMessageBox"
#include "settingsKeeper.h"

#include "xlsxdocument.h"


class AtomConversion : public QWidget
{
    Q_OBJECT
public:
    //Конструктор, принимате на вход ссылку на UI, параметр сохранения последнего пути
    explicit AtomConversion(Ui::MainWindow *ui, SettingsKeeper *settings,QWidget *parent = nullptr);
    //Метод конвертации атомов в другую СК
    void convertAtoms();
    //Метод конвертации атомов в другую СК и поиск их в ней
    void convertAndSearchAtoms();

private:
    //Вспомогательнй метод конвертации координат
     QVector<QVector<double>> convert() const;
    SettingsKeeper* settings;
    Ui::MainWindow *ui;
};

#endif // ATOMCONVERSION_H
