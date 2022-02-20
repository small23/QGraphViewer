// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "mainwindow.h"
#include "constantsandstrings.h"

int main(int argc, char *argv[])
{
	#ifndef OWN_HIGHDPI_SCALE
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
	#else
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QGuiApplication::setAttribute(Qt::AA_DisableHighDpiScaling, true);
    //QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
	#endif

    QApplication application(argc, argv);
    QPixmap pixmap(":/splash/splash.png");
    QRect rec = QApplication::desktop()->screenGeometry();
#ifndef OWN_HIGHDPI_SCALE
    int targetWidth = (rec.width() * qApp->devicePixelRatio()) / 2 * qApp->devicePixelRatio();
    int targetHeight = (rec.height() * qApp->devicePixelRatio()) / 2 * qApp->devicePixelRatio();
#else
    qreal scale = QGuiApplication::screens().at(0)->logicalDotsPerInch() / 96.0;
    int targetWidth = rec.width()  / 2 * scale;
    int targetHeight = rec.height() / 2 * scale;
#endif
    pixmap.setDevicePixelRatio(qApp->devicePixelRatio());
    QPixmap splashPixmap = pixmap.scaled(targetWidth, targetHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
	QSplashScreen splash(splashPixmap);
    qreal temp = splash.devicePixelRatioF();
    splash.show();
    QApplication::processEvents();
    QApplication::setOrganizationName("KemSU");
    QApplication::setApplicationName("QGraphViewer");
	MainWindow w;
    w.setLocale(QLocale(QLocale::English));
    QLocale::setDefault(QLocale::English);
    QApplication::processEvents();
    splash.finish(&w);
    return QApplication::exec();
}
