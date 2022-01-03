// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "helpmatrixwidget.h"

#include "constantsandstrings.h"
#include "QDebug"

HelpMatrixWidget::HelpMatrixWidget(Ui::MainWindow *uiInt, const QRect windowLocation, QWidget *parent) : QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    //view = new QGraphicsView();
    const QString helpFile = QString(":resource/help/HELP2.png");
    const QPixmap hel = QPixmap(helpFile);
    scene->addPixmap(hel);
    this->setScene(scene);

    const int centreX = windowLocation.x() + windowLocation.width() / 2;
    const int centreY = windowLocation.y() + windowLocation.height() / 2;
    const int height = hel.height() + 10;
    const int width = hel.width() + 20;
	int x = centreX - width / 2;
	int y = centreY - height / 2;

	if (x < 0) x = 0;
	if (y < 30) y = 30;
	
	this->setGeometry(x, y,
		width, height);
    this->setMaximumSize(hel.width()+20,hel.height()+10);
    this->setMinimumSize(hel.width()+20,hel.height()+10);
    this->setWindowTitle(STR_Window_Help);
    this->setAttribute(Qt::WA_DeleteOnClose);
    ui=uiInt;
    this->show();
}


void HelpMatrixWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
       QTableWidgetItem *itm;
       const QPoint& pos = event->pos();
       if (pos.x()>60 && pos.x()<190)
       {
           if (pos.y()>57 && pos.y()<210)
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
           else if (pos.y()>220 && pos.y()<365)
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
           else if (pos.y()>375 && pos.y()<530)
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
       else if (pos.x()>230 && pos.x()<330)
       {
           if (pos.y()>57 && pos.y()<210)
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
           else if (pos.y()>220 && pos.y()<365)
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
           else if (pos.y()>375 && pos.y()<530)
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
       else if (pos.x()>400 && pos.x()<524)
       {
           if (pos.y()>57 && pos.y()<210)
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
           else if (pos.y()>220 && pos.y()<365)
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
           else if (pos.y()>375 && pos.y()<530)
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
       else if (pos.x()>585 && pos.x()<700)
       {
           if (pos.y()>57 && pos.y()<210)
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
           else if (pos.y()>220 && pos.y()<365)
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
           else if (pos.y()>375 && pos.y()<530)
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
