#ifndef HELPWINDOW_H
#define HELPWINDOW_H

//Класс вывода графической справки

#include <QObject>
#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QCloseEvent>
#include <QMessageBox>

class HelpWindow : public QWidget
{
    Q_OBJECT
public:
    explicit HelpWindow(QPixmap hel,QRect windowLocation,QWidget *parent = nullptr);
    //~HelpWindow();
    QGraphicsScene *scene;
    QGraphicsView *view;

};

#endif // HELPWINDOW_H
