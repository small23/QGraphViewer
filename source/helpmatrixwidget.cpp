// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "helpmatrixwidget.h"

HelpMatrixWidget::HelpMatrixWidget(Ui::MainWindow *uiInt, const QRect windowLocation, const QRect desktopSize, QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    const QString helpFile = QString(":resource/help/HELP2.png");
    hel = QPixmap(helpFile);
    int h = hel.height();
    int w = hel.width();
    h = h * (96.0 * this->devicePixelRatioF() / 300.0);
    QPixmap outHel = hel.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    scaleRatioError = static_cast<double>(outHel.width()) / this->devicePixelRatioF() / origScaleW;
    outHel.setDevicePixelRatio(this->devicePixelRatioF());
    
    scene->addPixmap(outHel);
    this->setScene(scene);
    const int sizeLimWidth = desktopSize.width() - desktopSize.width() * 0.1;
    const int sizeLimHeight = desktopSize.height() - desktopSize.height() * 0.1;
    const int centreX = windowLocation.x() + windowLocation.width() / 2;
    const int centreY = windowLocation.y() + windowLocation.height() / 2;
    const int height = (outHel.height() / this->devicePixelRatioF()) < (sizeLimHeight) ? (outHel.height() / this->devicePixelRatioF()) + 10 : sizeLimHeight;
    const int width = (outHel.width() / this->devicePixelRatioF()) < (sizeLimWidth) ? (outHel.width() / this->devicePixelRatioF()) + 20 : sizeLimWidth;
	int x = centreX - width / 2;
	int y = centreY - height / 2;

	if (x < 0) x = 0;
	if (y < 30) y = 30;
	
	this->setGeometry(x, y,
		width, height);
    this->setMaximumSize(width, height);
    this->setMinimumSize(width, height);
    this->setWindowTitle(STR_Window_Help);
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui=uiInt;
    this->show();
}

void HelpMatrixWidget::resizeEvent(QResizeEvent* event)
{
    QGraphicsView::resizeEvent(event);
    int h = hel.height();
    int w = hel.width();
    h = h * (96.0 * this->devicePixelRatioF() / 300.0);
    QPixmap outHel = hel.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    outHel.setDevicePixelRatio(this->devicePixelRatioF());
    scene->clear();
    scene->addPixmap(outHel);
}

void HelpMatrixWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
       QTableWidgetItem *itm;
       const QPoint& pos = event->pos();
       if (pos.x()>(60* scaleRatioError) && pos.x()<(190 * scaleRatioError))
       {
           if (pos.y()>(57 * scaleRatioError) && pos.y()<(210 * scaleRatioError))
           {
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(0,0,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(0,1,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(0,2,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(1,0,itm);
               itm = new QTableWidgetItem("0.5");
               ui->tab3RotationTable->setItem(1,1,itm);
               itm = new QTableWidgetItem("-0.5");
               ui->tab3RotationTable->setItem(1,2,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(2,0,itm);
               itm = new QTableWidgetItem("0.5");
               ui->tab3RotationTable->setItem(2,1,itm);
               itm = new QTableWidgetItem("0.5");
               ui->tab3RotationTable->setItem(2,2,itm);
               this->close();
               this->destroy();

           }
           else if (pos.y()>(220 * scaleRatioError) && pos.y()<(365 * scaleRatioError))
           {
               itm = new QTableWidgetItem("0.5");
               ui->tab3RotationTable->setItem(0,0,itm);
               itm = new QTableWidgetItem("-0.5");
               ui->tab3RotationTable->setItem(0,1,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(0,2,itm);
               itm = new QTableWidgetItem("0.5");
               ui->tab3RotationTable->setItem(1,0,itm);
               itm = new QTableWidgetItem("0.5");
               ui->tab3RotationTable->setItem(1,1,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(1,2,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(2,0,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(2,1,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(2,2,itm);
               this->close();
               this->destroy();
           }
           else if (pos.y()>(375 * scaleRatioError) && pos.y()<(530 * scaleRatioError))
           {
               itm = new QTableWidgetItem("-0.5");
               ui->tab3RotationTable->setItem(0,0,itm);
               itm = new QTableWidgetItem("0.5");
               ui->tab3RotationTable->setItem(0,1,itm);
               itm = new QTableWidgetItem("0.5");
               ui->tab3RotationTable->setItem(0,2,itm);
               itm = new QTableWidgetItem("0.5");
               ui->tab3RotationTable->setItem(1,0,itm);
               itm = new QTableWidgetItem("-0.5");
               ui->tab3RotationTable->setItem(1,1,itm);
               itm = new QTableWidgetItem("0.5");
               ui->tab3RotationTable->setItem(1,2,itm);
               itm = new QTableWidgetItem("0.5");
               ui->tab3RotationTable->setItem(2,0,itm);
               itm = new QTableWidgetItem("0.5");
               ui->tab3RotationTable->setItem(2,1,itm);
               itm = new QTableWidgetItem("-0.5");
               ui->tab3RotationTable->setItem(2,2,itm);
               this->close();
               this->destroy();
           }
       }
       else if (pos.x()>(230 * scaleRatioError) && pos.x()<(330 * scaleRatioError))
       {
           if (pos.y()>57 * scaleRatioError && pos.y()<210 * scaleRatioError)
           {
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(0,0,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(0,1,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(0,2,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(1,0,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(1,1,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(1,2,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(2,0,itm);
               itm = new QTableWidgetItem("-1");
               ui->tab3RotationTable->setItem(2,1,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(2,2,itm);
               this->close();
               this->destroy();
           }
           else if (pos.y()>220 * scaleRatioError && pos.y()<365 * scaleRatioError)
           {
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(0,0,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(0,1,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(0,2,itm);
               itm = new QTableWidgetItem("-1");
               ui->tab3RotationTable->setItem(1,0,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(1,1,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(1,2,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(2,0,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(2,1,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(2,2,itm);
               this->close();
               this->destroy();
           }
           else if (pos.y()>375 * scaleRatioError && pos.y()<530 * scaleRatioError)
           {
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(0,0,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(0,1,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(0,2,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(1,0,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(1,1,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(1,2,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(2,0,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(2,1,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(2,2,itm);
               this->close();
               this->destroy();
           }
       }
       else if (pos.x()>400 * scaleRatioError && pos.x()<524 * scaleRatioError)
       {
           if (pos.y()>57 * scaleRatioError && pos.y()<210 * scaleRatioError)
           {
               itm = new QTableWidgetItem("0.5");
               ui->tab3RotationTable->setItem(0,0,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(0,1,itm);
               itm = new QTableWidgetItem("0.5");
               ui->tab3RotationTable->setItem(0,2,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(1,0,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(1,1,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(1,2,itm);
               itm = new QTableWidgetItem("-0.5");
               ui->tab3RotationTable->setItem(2,0,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(2,1,itm);
               itm = new QTableWidgetItem("0.5");
               ui->tab3RotationTable->setItem(2,2,itm);
               this->close();
               this->destroy();
           }
           else if (pos.y()>220 * scaleRatioError && pos.y()<365 * scaleRatioError)
           {
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(0,0,itm);
               itm = new QTableWidgetItem("0.5");
               ui->tab3RotationTable->setItem(0,1,itm);
               itm = new QTableWidgetItem("0.5");
               ui->tab3RotationTable->setItem(0,2,itm);
               itm = new QTableWidgetItem("0.5");
               ui->tab3RotationTable->setItem(1,0,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(1,1,itm);
               itm = new QTableWidgetItem("0.5");
               ui->tab3RotationTable->setItem(1,2,itm);
               itm = new QTableWidgetItem("0.5");
               ui->tab3RotationTable->setItem(2,0,itm);
               itm = new QTableWidgetItem("0.5");
               ui->tab3RotationTable->setItem(2,1,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(2,2,itm);
               this->close();
               this->destroy();
           }
           else if (pos.y()>375 * scaleRatioError && pos.y()<530 * scaleRatioError)
           {
               itm = new QTableWidgetItem("0.6666666");
               ui->tab3RotationTable->setItem(0,0,itm);
               itm = new QTableWidgetItem("-0.3333333");
               ui->tab3RotationTable->setItem(0,1,itm);
               itm = new QTableWidgetItem("-0.3333333");
               ui->tab3RotationTable->setItem(0,2,itm);
               itm = new QTableWidgetItem("0.3333333");
               ui->tab3RotationTable->setItem(1,0,itm);
               itm = new QTableWidgetItem("0.3333333");
               ui->tab3RotationTable->setItem(1,1,itm);
               itm = new QTableWidgetItem("-0.6666666");
               ui->tab3RotationTable->setItem(1,2,itm);
               itm = new QTableWidgetItem("0.3333333");
               ui->tab3RotationTable->setItem(2,0,itm);
               itm = new QTableWidgetItem("0.3333333");
               ui->tab3RotationTable->setItem(2,1,itm);
               itm = new QTableWidgetItem("0.3333333");
               ui->tab3RotationTable->setItem(2,2,itm);
               this->close();
               this->destroy();
           }
       }
       else if (pos.x()>585 * scaleRatioError && pos.x()<700 * scaleRatioError)
       {
           if (pos.y()>57 * scaleRatioError && pos.y()<210 * scaleRatioError)
           {
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(0,0,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(0,1,itm);
               itm = new QTableWidgetItem("-1");
               ui->tab3RotationTable->setItem(0,2,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(1,0,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(1,1,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(1,2,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(2,0,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(2,1,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(2,2,itm);
               this->close();
               this->destroy();
           }
           else if (pos.y()>220 * scaleRatioError && pos.y()<365 * scaleRatioError)
           {
               itm = new QTableWidgetItem("-1");
               ui->tab3RotationTable->setItem(0,0,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(0,1,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(0,2,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(1,0,itm);
               itm = new QTableWidgetItem("-1");
               ui->tab3RotationTable->setItem(1,1,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(1,2,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(2,0,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(2,1,itm);
               itm = new QTableWidgetItem("-1");
               ui->tab3RotationTable->setItem(2,2,itm);
               this->close();
               this->destroy();
           }
           else if (pos.y()>375 * scaleRatioError && pos.y()<530 * scaleRatioError)
           {
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(0,0,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(0,1,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(0,2,itm);
               itm = new QTableWidgetItem("-1");
               ui->tab3RotationTable->setItem(1,0,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(1,1,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(1,2,itm);
               itm = new QTableWidgetItem("0");
               ui->tab3RotationTable->setItem(2,0,itm);
               itm = new QTableWidgetItem("-1");
               ui->tab3RotationTable->setItem(2,1,itm);
               itm = new QTableWidgetItem("1");
               ui->tab3RotationTable->setItem(2,2,itm);
               this->close();
               this->destroy();
           }
       }

}
