// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    QGuiApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);

    QApplication application(argc, argv);
    //QTranslator qtTranslator;
    //auto a = QLibraryInfo::TranslationsPath;
    //qtTranslator.load("qt_en.qm", QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    //application.installTranslator(&qtTranslator);
    const QPixmap pixmap(":/splash/splash.png");
    QSplashScreen splash(pixmap);
    splash.setMask(pixmap.mask());
    splash.show();
    QApplication::processEvents();
    QApplication::setOrganizationName("KemSU");
    QApplication::setApplicationName("QGraphViewer");
	MainWindow w;
    QApplication::processEvents();
    splash.finish(&w);
    return QApplication::exec();
}
