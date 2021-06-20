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
    QApplication application(argc, argv);

    const QPixmap pixmap(":/splash/splash.png");
    QSplashScreen splash(pixmap);
    splash.setMask(pixmap.mask());
    splash.show();
    QApplication::processEvents();
    QApplication::setOrganizationName("KemSU");
    QApplication::setApplicationName("QGraphViewer");
	MainWindow w;
    const QString locale = QLocale::system().name();
    QTranslator qtTranslator;
    if (qtTranslator.load("qt_" + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
	    QApplication::installTranslator(&qtTranslator);
    w.setLocale(QLocale::English);
    w.setStatusBar(nullptr);
    w.setFixedSize(w.size());
    w.setWindowTitle("QGraphViewer");
    w.show();
    splash.finish(&w);
    return QApplication::exec();
}
