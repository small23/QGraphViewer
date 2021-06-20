#include "uiinit.h"
#include "ui_mainwindow.h"
#include "QObject"
#include "delegator.h"
#include "plotparameters.h"

auto lineTypesLang ={QComboBox::tr("Сплошная"), QComboBox::tr("Тире"), QComboBox::tr("Точка"), QComboBox::tr("Точка-тире")};
auto pointTypesLang = {QComboBox::tr("Круг"),QComboBox::tr("Плюс"),QComboBox::tr("Звездочка"),QComboBox::tr("Точка"),
                   QComboBox::tr("Перекрестие"),QComboBox::tr("Квадрат"),QComboBox::tr("Ромб"),QComboBox::tr("Верхнеор. треугольник"),
                   QComboBox::tr("Нижнеор. треугольник")};
auto rotateTypesLang = { QComboBox::tr("Нет"),QComboBox::tr("По часовой"),QComboBox::tr("Против часовой")};
auto pointTypesSecondLang = {QComboBox::tr("Сплошная"), QComboBox::tr("Тире"), QComboBox::tr("Точка"), QComboBox::tr("Точка-тире")};

void setupUiFields(Ui::MainWindow* ui)
{
    ui->tab1LineType1->addItems(lineTypesLang);
    ui->tab1LineType2->addItems(lineTypesLang);
    ui->tab1LineType3->addItems(lineTypesLang);
    ui->tab1LineType4->addItems(lineTypesLang);
    ui->tab1LineType5->addItems(pointTypesLang);
    ui->tab1LineType6->addItems(pointTypesLang);
    ui->tab1LineType5->setCurrentIndex(3);
    ui->tab1LineType6->setCurrentIndex(3);
    ui->tab3SurfRotationSelector->addItems({"0°","90°","180°","270°"});
    ui->tab2ComboBoxDosRotate->addItems(rotateTypesLang);
	ui->tab1ComboBoxRotate->addItems({ "0°","90°","180°","270°" });
    ui->tab2ComboBoxLineType->addItems(pointTypesSecondLang);
    ui->tab2ComboBoxLineSelector->addItems({"1"});

    ui->tab1FontSize->setLocale(QLocale::English);

    //QDoubleValidator *localValidator = new QDoubleValidator();
    QRegExpValidator* localValidator = new QRegExpValidator(QRegExp(R"([+-]?\d*[\.]?\d+)"));
    //localValidator->setLocale(QLocale::English);

    ui->tab1AtomsCutOff->setValidator(localValidator);
    ui->tab2DOSXMin->setValidator(localValidator);
    ui->tab2DOSXMax->setValidator(localValidator);
    ui->tab2DOSYMin->setValidator(localValidator);
    ui->tab2DOSYMax->setValidator(localValidator);
    ui->tab2ZoneStructYMin->setValidator(localValidator);
    ui->tab2ZoneStructYMax->setValidator(localValidator);
    ui->tab3ZoneStructYMin->setValidator(localValidator);
    ui->tab3ZoneStructYMax->setValidator(localValidator);


    QFont font("Arial", 9, QFont::Thin);

    int columnWidth=53;
    int rowHeight=8;


    ui->tab3RotationTable->setRowCount(3);
    ui->tab3RotationTable->setColumnCount(3);
    ui->tab3RotationTable->horizontalHeader()->hide();
    ui->tab3RotationTable->verticalHeader()->hide();
    ui->tab3RotationTable->verticalHeader()->setDefaultSectionSize(rowHeight);
    ui->tab3RotationTable->horizontalHeader()->setDefaultSectionSize(columnWidth);
    ui->tab3RotationTable->horizontalHeader()->setStretchLastSection(true);
    ui->tab3RotationTable->verticalHeader()->setStretchLastSection(true);


    for (int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            QTableWidgetItem *itm;
            if (i==j)
                itm=new QTableWidgetItem("1");
            else
                itm=new QTableWidgetItem("0");
            ui->tab3RotationTable->setItem(i,j,itm);
        }
    }
    ui->tab3RotationTable->setItemDelegate(new Delegator);

    ui->tab3ConvertedAtomsTable->setRowCount(0);
    ui->tab3ConvertedAtomsTable->setColumnCount(5);
    ui->tab3ConvertedAtomsTable->setHorizontalHeaderLabels(QStringList() << "№ исх. ат." << "№ ат. в элм. яч." << "n1" << "n2" << "n3");
    ui->tab3ConvertedAtomsTable->verticalHeader()->hide();
    ui->tab3ConvertedAtomsTable->verticalHeader()->setDefaultSectionSize(rowHeight);
    ui->tab3ConvertedAtomsTable->setColumnWidth(0,80);
    ui->tab3ConvertedAtomsTable->setColumnWidth(1,95);
    ui->tab3ConvertedAtomsTable->setColumnWidth(2,33);
    ui->tab3ConvertedAtomsTable->setColumnWidth(3,33);
    ui->tab3ConvertedAtomsTable->setColumnWidth(4,33);
    ui->tab3ConvertedAtomsTable->horizontalHeader()->setStretchLastSection(true);
    //ui->tab3ConvertedAtomsTable->verticalHeader()->setStretchLastSection(true);


    ui->tab2PDOSNumbersTable->setColumnCount(6);
    ui->tab2PDOSNumbersTable->setRowCount(0);
    ui->tab2PDOSNumbersTable->verticalHeader()->setDefaultSectionSize(rowHeight);
    ui->tab2PDOSNumbersTable->setColumnWidth(0,65);
    ui->tab2PDOSNumbersTable->setColumnWidth(1,55);
    ui->tab2PDOSNumbersTable->setColumnWidth(2,55);
    ui->tab2PDOSNumbersTable->setColumnWidth(3,75);
    ui->tab2PDOSNumbersTable->setColumnWidth(4,85);
    ui->tab2PDOSNumbersTable->setColumnWidth(5,85);
    ui->tab2PDOSNumbersTable->verticalHeader()->hide();
    ui->tab2PDOSNumbersTable->verticalScrollBar()->show();
    ui->tab2PDOSNumbersTable->horizontalHeader()->setStretchLastSection(true);
    //ui->tab2PDOSNumbersTable->verticalHeader()->setStretchLastSection(true);
    ui->tab2PDOSNumbersTable->setHorizontalHeaderLabels(QStringList() << "№ атома" << "Атом" << "Тип" << "Число ф-й" << "№ нач." <<"№ кон.");
    ui->tab2PDOSNumbersTable->horizontalHeader()->setFont(font);

    QPixmap pixmap(":logos/Logos/qcp-logo.png");
    ui->tab4QCustomPlotLabel->setPixmap(pixmap);

    QPixmap pixmap2(":logos/Logos/Qt_logo_2016.svg.png");
    ui->tab4QtLogo->setPixmap(pixmap2);

    QPixmap pixmap3(":logos/Logos/QXlsx-Desktop.png");
    ui->tab4QXlsxLogo->setPixmap(pixmap3);

    ui->tab4CompileDate->setText(QString("Дата сборки: %1, %2").arg(__DATE__).arg(__TIME__));

    ui->tab4TextBrowserAboutProgram->setFrameStyle(QFrame::NoFrame);
    ui->tab4TextBrowserAboutProgram->setTextInteractionFlags(Qt::NoTextInteraction);
}

void setUiButtonsGroups(Ui::MainWindow* ui)
{
    ui->DeleteButtonGroup->addButton(ui->deleteButton7);
    ui->DeleteButtonGroup->addButton(ui->deleteButton8);

    ui->DeleteButtonGroup->setId(ui->deleteButton1,1);
    ui->DeleteButtonGroup->setId(ui->deleteButton2,2);
    ui->DeleteButtonGroup->setId(ui->deleteButton3,3);
    ui->DeleteButtonGroup->setId(ui->deleteButton4,4);
    ui->DeleteButtonGroup->setId(ui->deleteButton5,5);
    ui->DeleteButtonGroup->setId(ui->deleteButton6,6);
    ui->DeleteButtonGroup->setId(ui->deleteButton7,7);
    ui->DeleteButtonGroup->setId(ui->deleteButton8,8);

    ui->ColorButtonGroup->addButton(ui->tab2ColorButtonFermiL);
    ui->ColorButtonGroup->addButton(ui->tab2ColorButton1);

    ui->ColorButtonGroup->setId(ui->tab1ColorButtonTrajgrad,1);
    ui->ColorButtonGroup->setId(ui->tab1ColorButtonAtomBass1,2);
    ui->ColorButtonGroup->setId(ui->tab1ColorButtonAtomBass2,3);
    ui->ColorButtonGroup->setId(ui->tab1ColorButtonConnections,4);
    ui->ColorButtonGroup->setId(ui->tab1ColorButtonPoints,5);
    ui->ColorButtonGroup->setId(ui->tab1ColorButtonAtoms,6);
    ui->ColorButtonGroup->setId(ui->tab2ColorButtonFermiL,7);
    ui->ColorButtonGroup->setId(ui->tab2ColorButton1,8);

    ui->HelpButtonGroup->addButton(ui->helpButton2);
    ui->HelpButtonGroup->addButton(ui->helpButton3);
    ui->HelpButtonGroup->addButton(ui->helpButton4);
    ui->HelpButtonGroup->addButton(ui->helpButton5);

    ui->HelpButtonGroup->setId(ui->helpButton1,1);
    ui->HelpButtonGroup->setId(ui->helpButton2,2);
    ui->HelpButtonGroup->setId(ui->helpButton3,3);
    ui->HelpButtonGroup->setId(ui->helpButton4,4);
    ui->HelpButtonGroup->setId(ui->helpButton5,5);
    ui->HelpButtonGroup->setId(ui->helpButton61,61);
    ui->HelpButtonGroup->setId(ui->helpButton62,62);
    ui->HelpButtonGroup->setId(ui->helpButton63,63);

    //ui->LoadFileButtonGroup->addButton(ui->tab2LoadFilef25DOSS);
    ui->LoadFileButtonGroup->addButton(ui->tab2LoadFilef25ZoneStruct);

    ui->LoadFileButtonGroup->setId(ui->tab1LoadFilef25,6);
    ui->LoadFileButtonGroup->setId(ui->tab1LoadFileOutp,5);
    //ui->LoadFileButtonGroup->setId(ui->tab2LoadFilef25DOSS,8);
    ui->LoadFileButtonGroup->setId(ui->tab2LoadFilef25ZoneStruct,7);
}

void setUiColorLabels(Ui::MainWindow* ui)
{
//    for (int i=0; i<6; i++)
//    {
//        LineColors[i].color=QColor(0,0,0);
//        LineColors[i].width=1;
//        LineColors[i].style=Qt::PenStyle::SolidLine;
//    }
    QPixmap colorIcon(16,16);
    colorIcon.fill(Qt::transparent);
    QPainter p(&colorIcon);
    p.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::transparent, 2);
    p.setPen(pen);
    QBrush brush(Qt::black);
    p.setBrush(brush);
    p.drawEllipse(0, 0, 16, 16);
    brush.setColor(Qt::black);
    p.setBrush(brush);
    p.drawEllipse(1, 1, 14, 14);
    QIcon redIcon(colorIcon);
    ui->ColorLable1->setPixmap(colorIcon);
    ui->ColorLable2->setPixmap(colorIcon);
    ui->ColorLable3->setPixmap(colorIcon);
    ui->ColorLable4->setPixmap(colorIcon);
    ui->ColorLable5->setPixmap(colorIcon);
    ui->ColorLable6->setPixmap(colorIcon);
    ui->ColorLable7->setPixmap(colorIcon);
    ui->ColorLable8->setPixmap(colorIcon);
    ui->ColorLable1->update();
    ui->ColorLable2->update();
    ui->ColorLable3->update();
    ui->ColorLable4->update();
    ui->ColorLable5->update();
    ui->ColorLable6->update();
    ui->ColorLable7->update();
    ui->ColorLable8->update();
}
