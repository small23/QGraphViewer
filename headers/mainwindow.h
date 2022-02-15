#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//Главная форма, класс обрабоки UI

#include <QMainWindow>
#include <QGraphicsView>
#include <QProgressDialog>
#include <QMessageBox>
#include <QApplication>
#include <QFont>
#include <QTimer>
#include <QtConcurrent/QtConcurrent>
#include <QProgressDialog>

#include "helpwindow.h"
#include "uiinit.h"
#include "graphicsdata.h"
#include "filedialogsload.h"
#include "helpmatrixwidget.h"
#include "atomconversion.h"
#include "banddata.h"
#include "surfdata.h"
#include "crystaltopondconvertors.h"
#include "filessaver.h"
#include "plotparameters.h"
#include "coloricondrawer.h"
#include "pdosparser.h"
#include "picturesettings.h"
#include "settingskeeper.h"
#include "ui_mainwindow.h"
#include "mathsymbols.h"
#include "changelog.h"
#include "basicgraph.h"
#include "zonegraph.h"
#include "dosgraph.h"
#include "constantsandstrings.h"
#include "qedos.h"
#include "qegraph.h"
#include "qesurfdata.h"
#include "qecontourgraph.h"
#include "structuresheaders.h"
#include "qezonedata.h"
#include "qezonegraph.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow final : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    //QProgressDialog* processDialog;

public Q_SLOTS:
    //Слот вызова меню настроек качества
    //и разрешения сохраняемых графиков
    void showPictureSettings();
	
    //Обработчики нажатий на кнопки формы
private Q_SLOTS:
    //...смены цвета линнии графика
    void colorChangeButtonClicked(int id) const;
    void setColotLabelById(int id) const;
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

    void tab4Changelog();

    void tab5QeDosLoad();

    void tab5UpdateParams(QString i);
    void tab5UpdateShowLine(int i);
    void tab5ComboBoxLineSelectorIndexChanged(int selected);
    void tab5BushButtonSetFontPressed();
    void tab5LoadFileDossPressed();
    void tab5DrawDosPressed();
    void tab5UpdateParamsFile(int selected);
    void tab5LanguageChanged();
    void tab5LoadSurfConvButtonPressed();
    void tab5LoadQEDenButtonPressed();
    void tab5PlotGraphicButtonPressed();
    void tab5PushButtonSetFontContourPressed();
    void tab5LoadQeBandButtonPressed();
    void tab5DrawZoneButtonPressed();

    void screenChanged(QScreen* screen);
	
private:
    //Указатели на классы-обработчики и хранилища
    SettingsKeeper *settings;
    //UI
    Ui::MainWindow *ui;
    PictureSettings *formPictureSettings = nullptr;
    changelog *formChangelog = nullptr;
    QFont tab1GraphFont;
    QFont tab2GraphFont;
    QFont tab5GraphFont;
    QFont tab5ContourGraphFont;
    GraphicsData *graphicsData;
    BandData *bandData;
    SurfData *surfData;
    QeDos* qeDosData;
    FilesSaver *filesSaver;
    PdosParser *pdosParser;
    QString compilationTime;
    CrystalTopondConvertors *ctConvertor;
    PlotParameters *plotParams;
    ColorIconDrawer *iconDrawer;
    MathSymbols* symbols;
    AtomConversion* atomsConvert;
	FileDialogsLoad*	fileDiag;
    QeSurfData* qeSurfData;
    QeZoneData* qeZoneData;
    QColor MenuSelectedGraph = Qt::darkGreen;
};
#endif // MAINWINDOW_H
