// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#ifndef HELPMATRIXWIDGET_H
#define HELPMATRIXWIDGET_H

//Класс выбора матрицы преобразования для конвертации атомов
//Реализует выбор матрицы по двойному щелчку мыши
#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QCloseEvent>
#include <QMessageBox>
#include "ui_mainwindow.h"
#include <QMouseEvent>
#include "constantsandstrings.h"
#include "QDebug"

class HelpMatrixWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit HelpMatrixWidget(Ui::MainWindow *ui, QRect windowLocation, QRect desktopSize, QWidget *parent = nullptr);
    QGraphicsScene *scene;
    //QGraphicsView *view;
    Ui::MainWindow *ui;
private slots:
    void mouseDoubleClickEvent(QMouseEvent * e) override;
    void resizeEvent(QResizeEvent* event) override;
    void closeEvent(QCloseEvent* event) override;

private:
    int origScaleW = 744;
    int origScaleH = 588;
    double scaleRatioError = 1;
    QPixmap hel;
};

#endif // HELPMATRIXWIDGET_H
