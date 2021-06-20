#include "mainwindow.h"

#include <QApplication>
#include <QStyleFactory>
#include <QtGlobal>

int main(int argc, char *argv[])
{
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling,true);
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy());
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy());
    QApplication a(argc, argv);

    QPixmap pixmap(":/splash/splash.png");
    QSplashScreen splash(pixmap);
    splash.setMask(pixmap.mask());
    splash.show();
    a.processEvents();
    a.setOrganizationName("KemSU");
    a.setApplicationName("QGraphViewer");
	MainWindow w;
    QString locale = QLocale::system().name();
    QTranslator qtTranslator;
    if (qtTranslator.load("qt_" + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
        a.installTranslator(&qtTranslator);
    w.setLocale(QLocale::English);
    w.setStatusBar(nullptr);
    w.setFixedSize(w.size());
    w.setWindowTitle("QGraphViewer");
    w.show();
    splash.finish(&w);
    return a.exec();
}
