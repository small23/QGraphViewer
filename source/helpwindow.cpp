// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "helpwindow.h"

#include "constantsandstrings.h"
#include "QScrollBar"


HelpWindow::HelpWindow(const QPixmap& hel, const QRect windowLocation, qreal devScaleRatio, QRect desktopSize,QWidget *parent) : QWidget(parent)
{
    scene = new QGraphicsScene();
    view = new QGraphicsView();
    int h = hel.height();
    int w = hel.width();
    h = h * (96.0 * devScaleRatio / 300.0);
    QPixmap outHel = hel.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    outHel.setDevicePixelRatio(devScaleRatio);
	scene->addPixmap(outHel);
    view->setScene(scene);
    int sizeLimWidth = desktopSize.width() - desktopSize.width() * 0.1;
    int sizeLimHeight = desktopSize.height() - desktopSize.height() * 0.1;
    const int centreX = windowLocation.x() + windowLocation.width() / 2;
    const int centreY = windowLocation.y() + windowLocation.height() / 2;
    const int height = (outHel.height() / devScaleRatio) < (sizeLimHeight) ? (outHel.height()/ devScaleRatio) + 10 : sizeLimHeight;
    const int width = (outHel.width() / devScaleRatio) < (sizeLimWidth) ? (outHel.width() / devScaleRatio) + 20 : sizeLimWidth;
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
