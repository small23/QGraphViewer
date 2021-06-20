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



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QProgressDialog* process_dialog;

public Q_SLOTS:
    //Слот вызова меню настроек качества
    //и разрешения сохраняемых графиков
    void showPictureSettings();
	
    //Обработчики нажатий на кнопки формы
private Q_SLOTS:
    //...смены цвета линнии графика
    void ColorChangeButtonClicked(int id);
    //...очищения строки пути к файлу
    void DeleteFileStringButtonClicked(int id);
    //...вызова графической справки
    void HelpButtonClicked(int id);
    //...построения графика во вкладе 1 (basicgraphbuild)
    void plotButtonTab1Clicked();
    //...смены шрифта надписей на графике
    void fontChangeButtonPressed();
    //...конвертации координат атомов (
    void atomsConvertButtonPressed();
    //...конвертации и поиска атомов в ячейках
    void atomsSearchButtonPressed();
    //...конвертации и сохранения X=f(x)-координат
    void LoadFileConvertXfXButtonPressed();
    //...конвертации и сохранения DOS-файлов
    void tab3LoadFilesConvertDOSButtonPressed();
    //...конвертации и сохранения поверхностей из *.f25 файлов
    void tab3SurfF25ButtonPressed();
    //...конвертации и сохранения поверхностей из стандартных файлов
    void tab3SurfConvertButtonPressed();
    //...конвертации и сохранения файлов-конфигураций Crystal в Topond
    void tab3ButtonCrystalToTopondPressed();
    //...конвертации и сохранения файлов-конфигураций Topond в Crystal
    void tab3ButtonTopondToCrystalPressed();
    //...построения графика зоонной структуры во вкладе 2 (ZoneStructGraphBuilder)
    void tab2buttonDrawZoneStructPressed();
    //...обновления параметров построения линии выбранной в окне настройки линии (вкладка 2)
    void tab2UpdateParams(QString i);
    //...обновления параметров отображения линии на графике и подсветка линии
    void tab2UpdateShowLine(int i);
    //...загрузки, чтения содержимого f25 dos файлов и вывода содержимого в дроп-лист номера графика
    void tab2LoadFilef25DOSSPressed();
    //...обработчик смены выбранной линни графика и отображение его настроек
    void tab2ComboBoxLineSelectorIndexChanged(int selected);
    //...построения DOS графика во вкладке 2 (DOSGraphBuilder)
    void tab2ButtonDrawDOSPressed();
    //...вызова функции выбора шрифта на 2 вкладке
    void tab2BushButtonSetFontPressed();
    //...вызова окна про версию Qt
    void tab4QtAbout();
    //...вызова окна лицензии
    void tab4LicenceMIT();
    //...загрузки файла PDOS, обработки данных и вывода результатов в таблицу
    void tab2PushButtonPDOSLoadPressed();
    //Обработчик вызова таймера очистки памяти от графиков
    void garbageCollector();

	
private:
    //Указатели на классы-обработчики и хранилища
    SettingsKeeper *settings;
    //UI
    Ui::MainWindow *ui;
    PictureSettings *form = nullptr;
    QFont tab1GraphFont;
    QFont tab2GraphFont;
    GraphicsData *graphicsData;
    BandData *bandData;
    SurfData *surfData;
    FilesSaver *filesSaver;
    PdosParser *pdosParser;
    QString compilationTime;
    CrystalTopondConvertors *CTConvertor;
    PlotParameters *plotParams;
    ColorIconDrawer *iconDrawer;
    QTimer* tmr;
    QVector<BasicGraphBuild*> *GraphsA;
    QVector<DOSGraphBuilder*> *GraphsB;
    QVector<ZoneStructGraphBuilder*> *GraphsC;
    MathSymbols* symbols;
    AtomConversion* atomsConvert;
};
#endif // MAINWINDOW_H
