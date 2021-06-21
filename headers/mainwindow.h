#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Главная форма, класс обрабоки UI

#include <QMainWindow>
#include <QGraphicsView>
#include <QProgressDialog>
#include <structuresHeaders.h>
#include <QMessageBox>

#include <QFont>

#include <QProgressDialog>
#include "helpwindow.h"
#include "uiinit.h"
#include "basicgraphbuild.h"
#include "graphicsdata.h"
#include "zonestructgraphbuilder.h"
#include "filedialogsload.h"
#include "helpmatrixwidget.h"
#include "atomconversion.h"
#include "banddata.h"
#include "surfdata.h"
#include "crystaltopondconvertors.h"
#include "filessaver.h"
#include "plotparameters.h"
#include "coloricondrawer.h"
#include "dosgraphbuilder.h"
#include "pdosparser.h"
#include <QTimer>
#include <QtConcurrent/QtConcurrent>
#include "picturesettings.h"
#include "settingsKeeper.h"
#include "ui_mainwindow.h"
#include "mathsymbols.h"
#include "changelog.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //QProgressDialog* processDialog;

public Q_SLOTS:
    //Слот вызова меню настроек качества
    //и разрешения сохраняемых графиков
    void showPictureSettings();
	
    //Обработчики нажатий на кнопки формы
private Q_SLOTS:
    //...смены цвета линнии графика
    void colorChangeButtonClicked(int id) const;
    //...очищения строки пути к файлу
    void deleteFileStringButtonClicked(int id) const;
    //...вызова графической справки
    void helpButtonClicked(int id);
    //...построения графика во вкладе 1 (basicgraphbuild)
    void plotButtonTab1Clicked();
    //...смены шрифта надписей на графике
    void fontChangeButtonPressed();
    //...конвертации координат атомов (
    void atomsConvertButtonPressed() const;
    //...конвертации и поиска атомов в ячейках
    void atomsSearchButtonPressed() const;
    //...конвертации и сохранения X=f(x)-координат
    void loadFileConvertXfXButtonPressed();
    //...конвертации и сохранения DOS-файлов
    void tab3LoadFilesConvertDosButtonPressed();
    //...конвертации и сохранения поверхностей из *.f25 файлов
    void tab3SurfF25ButtonPressed();
    //...конвертации и сохранения поверхностей из стандартных файлов
    void tab3SurfConvertButtonPressed();
    //...конвертации и сохранения файлов-конфигураций Crystal в Topond
    void tab3ButtonCrystalToTopondPressed();
    //...конвертации и сохранения файлов-конфигураций Topond в Crystal
    void tab3ButtonTopondToCrystalPressed();
    //...построения графика зоонной структуры во вкладе 2 (ZoneStructGraphBuilder)
    void tab2ButtonDrawZoneStructPressed();
    //...обновления параметров построения линии выбранной в окне настройки линии (вкладка 2)
    void tab2UpdateParams(QString i) const;
    //...обновления параметров отображения линии на графике и подсветка линии
    void tab2UpdateShowLine(int i) const;
    //...загрузки, чтения содержимого f25 dos файлов и вывода содержимого в дроп-лист номера графика
    void tab2LoadFilef25DossPressed();
    //...обработчик смены выбранной линни графика и отображение его настроек
    void tab2ComboBoxLineSelectorIndexChanged(int selected) const;
    //...построения DOS графика во вкладке 2 (DOSGraphBuilder)
    void tab2ButtonDrawDosPressed();
    //...вызова функции выбора шрифта на 2 вкладке
    void tab2BushButtonSetFontPressed();
    //...вызова окна про версию Qt
    void tab4QtAbout();
    //...вызова окна лицензии
    void tab4LicenceMit();
    //...загрузки файла PDOS, обработки данных и вывода результатов в таблицу
    void tab2PushButtonPdosLoadPressed();
    //Обработчик вызова таймера очистки памяти от графиков
    void garbageCollector() const;

    void tab4Changelog();
	
private:
    //Указатели на классы-обработчики и хранилища
    SettingsKeeper *settings;
    //UI
    Ui::MainWindow *ui;
    PictureSettings *formPictureSettings = nullptr;
    changelog *formChangelog = nullptr;
    QFont tab1GraphFont;
    QFont tab2GraphFont;
    GraphicsData *graphicsData;
    BandData *bandData;
    SurfData *surfData;
    FilesSaver *filesSaver;
    PdosParser *pdosParser;
    QString compilationTime;
    CrystalTopondConvertors *ctConvertor;
    PlotParameters *plotParams;
    ColorIconDrawer *iconDrawer;
    QTimer* tmr;
    QVector<BasicGraphBuild*> *graphsA;
    QVector<DOSGraphBuilder*> *graphsB;
    QVector<ZoneStructGraphBuilder*> *graphsC;
    MathSymbols* symbols;
    AtomConversion* atomsConvert;
};
#endif // MAINWINDOW_H
