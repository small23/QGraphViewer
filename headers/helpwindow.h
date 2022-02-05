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
#include "QLabel"
#include "QVBoxLayout"

class HelpWindow : public QGraphicsView
{
    Q_OBJECT
public:
    explicit HelpWindow(const QPixmap& hel,QRect windowLocation, QRect desktopSize,QWidget *parent = nullptr);
    //~HelpWindow();
    QGraphicsScene *scene;
    //QGraphicsView *view;

private slots:
    void resizeEvent(QResizeEvent* event) override;
	void closeEvent(QCloseEvent* event) override;

private:
    QPixmap helInt;
    QRect windowLocationInt;
    QRect desktopSizeInt;

};

#endif // HELPWINDOW_H
