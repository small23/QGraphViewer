// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "mainwindow.h"

int main(int argc, char *argv[])
{

    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);

    QApplication application(argc, argv);
    QPixmap pixmap(":/splash/splash.png");
    QRect rec = QApplication::desktop()->screenGeometry();
    int targetWidth = (rec.width() * qApp->devicePixelRatio()) / 2 * qApp->devicePixelRatio();
    int targetHeight = (rec.height() * qApp->devicePixelRatio()) / 2 * qApp->devicePixelRatio();
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
