// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "helpwindow.h"

#include "constantsandstrings.h"
#include "QScrollBar"


HelpWindow::HelpWindow(const QPixmap& hel, const QRect windowLocation,QWidget *parent) : QWidget(parent)
{
    scene = new QGraphicsScene();
    view = new QGraphicsView();
    scene->addPixmap(hel);
    view->setScene(scene);
    //colorPickerMenu.setGeometry(windowLocation.x()+100,windowLocation.y()+50,522,393);
    const int centreX = windowLocation.x() + windowLocation.width() / 2;
    const int centreY = windowLocation.y() + windowLocation.height() / 2;
    const int height = hel.height() < 700 ? hel.height() + 10 : 700;
    const int width = hel.width() + 20;
	int x = centreX - width / 2;
	int y = centreY - height / 2;

	if (x < 0) x = 0;
	if (y < 30) y = 30;
	
    view->setGeometry(x,y,
		width,height);
	

	view->show();
	view->verticalScrollBar()->setValue(0);
    view->setWindowTitle(STR_Window_Help);
    view->setAttribute(Qt::WA_DeleteOnClose);
}
