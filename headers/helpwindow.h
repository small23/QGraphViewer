// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#ifndef HELPWINDOW_H
#define HELPWINDOW_H

//Класс вывода графической справки

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QCloseEvent>
#include <QMessageBox>
#include "constantsandstrings.h"
#include "QScrollBar"

class HelpWindow : public QWidget
{
    Q_OBJECT
public:
    explicit HelpWindow(const QPixmap& hel,QRect windowLocation, qreal devScaleRatio, QRect desktopSize,QWidget *parent = nullptr);
    //~HelpWindow();
    QGraphicsScene *scene;
    QGraphicsView *view;

};

#endif // HELPWINDOW_H
