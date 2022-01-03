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

class HelpMatrixWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit HelpMatrixWidget(Ui::MainWindow *ui, QRect windowLocation, qreal devScaleRatio, QRect desktopSize, QWidget *parent = nullptr);
    QGraphicsScene *scene;
    //QGraphicsView *view;
    Ui::MainWindow *ui;
public slots:
    void mouseDoubleClickEvent(QMouseEvent * e) override;

private:
    int origScaleW = 744;
    int origScaleH = 588;
    double scaleRatioError = 1;
};

#endif // HELPMATRIXWIDGET_H
