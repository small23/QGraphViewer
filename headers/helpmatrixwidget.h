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
    explicit HelpMatrixWidget(Ui::MainWindow *ui, QRect windowLocation, QWidget *parent = nullptr);
    QGraphicsScene *scene;
    //QGraphicsView *view;
    Ui::MainWindow *ui;
public slots:
    void mouseDoubleClickEvent(QMouseEvent * e) override;


};

#endif // HELPMATRIXWIDGET_H
