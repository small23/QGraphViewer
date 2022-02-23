// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "helpwindow.h"

#include <QApplication>
#include <qscreen.h>
#include <qthread.h>

HelpWindow::HelpWindow(const QPixmap& hel, const QRect windowLocation, QRect desktopSize,QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    helInt = hel;
    desktopSizeInt = desktopSize;
    int h = hel.height();
    int w = hel.width();
#ifndef OWN_HIGHDPI_SCALE
    h = h * (96.0 * this->devicePixelRatioF() / 300.0);
    QPixmap outHel = hel.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    outHel.setDevicePixelRatio(this->devicePixelRatioF());
#else
    QScreen* pScreen = QGuiApplication::screenAt(this->mapToGlobal({ this->width() / 2,this->height() / 2 }));
    h = h * (pScreen->logicalDotsPerInch() / 300.0);
    QPixmap outHel = hel.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
#endif
	scene->addPixmap(outHel);
    this->setScene(scene);
    int sizeLimWidth = desktopSize.width() - desktopSize.width() * 0.1;
    int sizeLimHeight = desktopSize.height() - desktopSize.height() * 0.1;
    const int centreX = windowLocation.x() + windowLocation.width() / 2;
    const int centreY = windowLocation.y() + windowLocation.height() / 2;
    const int height = (outHel.height() / this->devicePixelRatioF()) < (sizeLimHeight) ? (outHel.height()/ this->devicePixelRatioF()) + 10 : sizeLimHeight;
    const int width = (outHel.width() / this->devicePixelRatioF()) < (sizeLimWidth) ? (outHel.width() / this->devicePixelRatioF()) + 20 : sizeLimWidth;
	int x = centreX - width / 2;
	int y = centreY - height / 2;

	if (x < 0) x = 0;
	if (y < 30) y = 30;
	
    this->setGeometry(x,y,
		width,height);
	

	//view->show();
	this->verticalScrollBar()->setValue(0);
    this->setWindowTitle(STR_Window_Help);
    this->setAttribute(Qt::WA_DeleteOnClose);

    this->show();
    
}

void HelpWindow::resizeEvent(QResizeEvent* event)
{
	int h = helInt.height();
    int w = helInt.width();
#ifndef OWN_HIGHDPI_SCALE
    QGraphicsView::resizeEvent(event);
    h = h * (96.0 * this->devicePixelRatioF() / 300.0);
    QPixmap outHel = helInt.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    outHel.setDevicePixelRatio(this->devicePixelRatioF());
#else
    QScreen* pScreen = this->screen();
    h = h * (pScreen->logicalDotsPerInch() / 300.0);
    QPixmap outHel = helInt.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    //outHel.setDevicePixelRatio(this->devicePixelRatioF());
#endif
    scene->clear();
    scene->addPixmap(outHel);

}

void HelpWindow::closeEvent(QCloseEvent* event)
{
	QGraphicsView::closeEvent(event);
    delete scene;
}
