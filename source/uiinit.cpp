// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "uiinit.h"

auto lineTypesLang = { STR_UI_LineTypes_Solid, STR_UI_LineTypes_Dash, STR_UI_LineTypes_Pointed, STR_UI_LineTypes_PointDash };
auto pointTypesLang = { STR_UI_PointTypes_Cirq,STR_UI_PointTypes_Plus,STR_UI_PointTypes_Star,STR_UI_PointTypes_Point,
				   STR_UI_PointTypes_X,STR_UI_PointTypes_Square,STR_UI_PointTypes_Diamond,STR_UI_PointTypes_TriangUp,
				   STR_UI_PointTypes_TriangDown };
auto rotateTypesLang = { STR_UI_RotateTypes_None,STR_UI_RotateTypes_Clockwise,STR_UI_RotateTypes_Counter_Clockwise };
auto pointTypesSecondLang = { STR_UI_LineTypes_Solid, STR_UI_LineTypes_Dash, STR_UI_LineTypes_Pointed, STR_UI_LineTypes_PointDash };

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
	ui->tab3SurfRotationSelector->addItems({ "0°","90°","180°","270°" });
	ui->tab2ComboBoxDosRotate->addItems(rotateTypesLang);
	ui->tab1ComboBoxRotate->addItems({ "0°","90°","180°","270°" });
	ui->tab5SurfRotationSelector->addItems({ "0°","90°","180°","270°" });
	ui->tab5ComboBoxRotate->addItems({ "0°","90°","180°","270°" });
	ui->tab2ComboBoxLineType->addItems(pointTypesSecondLang);
	ui->tab2ComboBoxLineSelector->addItems({ "1" });

	ui->tab5ComboBoxDosRotate->addItems(rotateTypesLang);
	ui->tab5ComboBoxLineType->addItems(pointTypesSecondLang);
	ui->tab5ComboBoxLineSelector->addItems({ "1" });

	ui->tab1FontSize->setLocale(QLocale::English);

	//QDoubleValidator *localValidator = new QDoubleValidator();
	QRegExpValidator* localValidator = new QRegExpValidator(QRegExp(R"(^[+\-]?(?:(?:0|[1-9]\d*)(?:\.\d*)?|\.\d+)(?:\d[eE][+\-]?\d+)?$)"));
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

	ui->tab5DOSXMin->setValidator(localValidator);
	ui->tab5DOSXMax->setValidator(localValidator);
	ui->tab5DOSYMin->setValidator(localValidator);
	ui->tab5DOSYMax->setValidator(localValidator);
	ui->tab5ZoneStructYMin->setValidator(localValidator);
	ui->tab5ZoneStructYMax->setValidator(localValidator);
	ui->tab5DOSFerm->setValidator(localValidator);
	ui->tab5DOSShift->setValidator(localValidator);

	const QFont font("Arial", 9, QFont::Thin);

	constexpr int columnWidth = 53;
	constexpr int rowHeight = 8;


	ui->tab3RotationTable->setRowCount(3);
	ui->tab3RotationTable->setColumnCount(3);
	ui->tab3RotationTable->horizontalHeader()->hide();
	ui->tab3RotationTable->verticalHeader()->hide();
	ui->tab3RotationTable->verticalHeader()->setDefaultSectionSize(rowHeight);
	ui->tab3RotationTable->horizontalHeader()->setDefaultSectionSize(columnWidth);
	ui->tab3RotationTable->horizontalHeader()->setStretchLastSection(true);
	ui->tab3RotationTable->verticalHeader()->setStretchLastSection(true);


	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			QTableWidgetItem* itm;
			if (i == j)
				itm = new QTableWidgetItem("1");
			else
				itm = new QTableWidgetItem("0");
			ui->tab3RotationTable->setItem(i, j, itm);
		}
	}
	ui->tab3RotationTable->setItemDelegate(new Delegator);

	ui->tab3ConvertedAtomsTable->setRowCount(0);
	ui->tab3ConvertedAtomsTable->setColumnCount(5);
	ui->tab3ConvertedAtomsTable->setHorizontalHeaderLabels(QStringList() << STR_XLSX_Short_SourceAtomNumber << STR_XLSX_Short_AtomNumber
		<< STR_XLSX_Extended_N1 << STR_XLSX_Extended_N2 << STR_XLSX_Extended_N3);
	//QStringList() << "№ исх. ат." << "№ ат. в элм. яч." << "n1" << "n2" << "n3");
	ui->tab3ConvertedAtomsTable->verticalHeader()->hide();
	ui->tab3ConvertedAtomsTable->verticalHeader()->setDefaultSectionSize(rowHeight);
	ui->tab3ConvertedAtomsTable->setColumnWidth(0, 80);
	ui->tab3ConvertedAtomsTable->setColumnWidth(1, 95);
	ui->tab3ConvertedAtomsTable->setColumnWidth(2, 33);
	ui->tab3ConvertedAtomsTable->setColumnWidth(3, 33);
	ui->tab3ConvertedAtomsTable->setColumnWidth(4, 33);
	ui->tab3ConvertedAtomsTable->horizontalHeader()->setStretchLastSection(true);


	ui->tab2PDOSNumbersTable->setColumnCount(6);
	ui->tab2PDOSNumbersTable->setRowCount(0);
	ui->tab2PDOSNumbersTable->verticalHeader()->setDefaultSectionSize(rowHeight);
	ui->tab2PDOSNumbersTable->setColumnWidth(0, 65);
	ui->tab2PDOSNumbersTable->setColumnWidth(1, 55);
	ui->tab2PDOSNumbersTable->setColumnWidth(2, 55);
	ui->tab2PDOSNumbersTable->setColumnWidth(3, 75);
	ui->tab2PDOSNumbersTable->setColumnWidth(4, 85);
	ui->tab2PDOSNumbersTable->setColumnWidth(5, 85);
	ui->tab2PDOSNumbersTable->verticalHeader()->hide();
	ui->tab2PDOSNumbersTable->verticalScrollBar()->show();
	ui->tab2PDOSNumbersTable->horizontalHeader()->setStretchLastSection(true);
	//ui->tab2PDOSNumbersTable->verticalHeader()->setStretchLastSection(true);
	ui->tab2PDOSNumbersTable->setHorizontalHeaderLabels(QStringList() << STR_XLSX_AtomNumber << STR_XLSX_Atom << STR_XLSX_Type << STR_XLSX_FunctionNumber << STR_XLSX_StartNumber << STR_XLSX_EndNumber);
	ui->tab2PDOSNumbersTable->horizontalHeader()->setFont(font);

	ui->tab4CompileDate->setText(STR_BuildDate.arg(__DATE__).arg(__TIME__));

	ui->tab4TextBrowserAboutProgram->setFrameStyle(QFrame::NoFrame);
	ui->tab4TextBrowserAboutProgram->setTextInteractionFlags(Qt::NoTextInteraction);
}

void imageInit(Ui::MainWindow* ui, qreal devPixRat)
{
#ifndef OWN_HIGHDPI_SCALE
	int w = (ui->tab4QtLogo->width()) * devPixRat;
	int h = (ui->tab4QtLogo->height() + 500) * devPixRat;
#endif
#ifdef OWN_HIGHDPI_SCALE
	int w = ui->tab4QtLogo->width();
	int h = ui->tab4QtLogo->height() + 500;
#endif
	QPixmap pixmap(":logos/Logos/qcp-logo.png");
#ifndef OWN_HIGHDPI_SCALE
	pixmap.setDevicePixelRatio(devPixRat);
#endif
	ui->tab4QCustomPlotLabel->setPixmap(pixmap.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation));

	QPixmap pixmap2(":logos/Logos/Qt_logo_2016.svg.png");

#ifndef OWN_HIGHDPI_SCALE
	pixmap2.setDevicePixelRatio(devPixRat);
#endif
	ui->tab4QtLogo->setPixmap(pixmap2.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation));

	QPixmap pixmap3(":logos/Logos/QXlsx-Desktop.png");
#ifndef OWN_HIGHDPI_SCALE
	pixmap3.setDevicePixelRatio(devPixRat);
#endif
	ui->tab4QXlsxLogo->setPixmap(pixmap3.scaled(w, h, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void setUiButtonsGroups(Ui::MainWindow* ui)
{
	//ui->tab5LoadFilecomboBox->view()->setMinimumWidth(400);
	ui->DeleteButtonGroup->addButton(ui->deleteButton7);
	ui->DeleteButtonGroup->addButton(ui->deleteButton8);
	ui->DeleteButtonGroup->addButton(ui->deleteButton9);
	ui->DeleteButtonGroup->addButton(ui->deleteButton10);
	ui->DeleteButtonGroup->addButton(ui->deleteButton11);

	ui->DeleteButtonGroup->setId(ui->deleteButton1, 1);
	ui->DeleteButtonGroup->setId(ui->deleteButton2, 2);
	ui->DeleteButtonGroup->setId(ui->deleteButton3, 3);
	ui->DeleteButtonGroup->setId(ui->deleteButton4, 4);
	ui->DeleteButtonGroup->setId(ui->deleteButton5, 5);
	ui->DeleteButtonGroup->setId(ui->deleteButton6, 6);
	ui->DeleteButtonGroup->setId(ui->deleteButton7, 7);
	ui->DeleteButtonGroup->setId(ui->deleteButton8, 8);
	ui->DeleteButtonGroup->setId(ui->deleteButton9, 9);
	ui->DeleteButtonGroup->setId(ui->deleteButton10, 10);
	ui->DeleteButtonGroup->setId(ui->deleteButton11, 11);

	ui->ColorButtonGroup->addButton(ui->tab2ColorButtonFermiL);
	ui->ColorButtonGroup->addButton(ui->tab2ColorButton1);
	ui->ColorButtonGroup->addButton(ui->tab5ColorButtonFermiL);
	ui->ColorButtonGroup->addButton(ui->tab5ColorButton1);

	ui->ColorButtonGroup->setId(ui->tab1ColorButtonTrajgrad, 1);
	ui->ColorButtonGroup->setId(ui->tab1ColorButtonAtomBass1, 2);
	ui->ColorButtonGroup->setId(ui->tab1ColorButtonAtomBass2, 3);
	ui->ColorButtonGroup->setId(ui->tab1ColorButtonConnections, 4);
	ui->ColorButtonGroup->setId(ui->tab1ColorButtonPoints, 5);
	ui->ColorButtonGroup->setId(ui->tab1ColorButtonAtoms, 6);
	ui->ColorButtonGroup->setId(ui->tab2ColorButtonFermiL, 7);
	ui->ColorButtonGroup->setId(ui->tab2ColorButton1, 8);
	ui->ColorButtonGroup->setId(ui->tab5ColorButton1, 9);
	ui->ColorButtonGroup->setId(ui->tab5ColorButtonFermiL, 10);

	ui->HelpButtonGroup->addButton(ui->helpButton2);
	ui->HelpButtonGroup->addButton(ui->helpButton3);
	ui->HelpButtonGroup->addButton(ui->helpButton4);
	ui->HelpButtonGroup->addButton(ui->helpButton5);

	ui->HelpButtonGroup->setId(ui->helpButton1, 1);
	ui->HelpButtonGroup->setId(ui->helpButton2, 2);
	ui->HelpButtonGroup->setId(ui->helpButton3, 3);
	ui->HelpButtonGroup->setId(ui->helpButton4, 4);
	ui->HelpButtonGroup->setId(ui->helpButton5, 5);
	ui->HelpButtonGroup->setId(ui->helpButton61, 61);
	ui->HelpButtonGroup->setId(ui->helpButton62, 62);
	ui->HelpButtonGroup->setId(ui->helpButton63, 63);

	ui->LoadFileButtonGroup->addButton(ui->tab2LoadFilef25ZoneStruct);

	ui->LoadFileButtonGroup->setId(ui->tab1LoadFilef25, 6);
	ui->LoadFileButtonGroup->setId(ui->tab1LoadFileOutp, 5);
	ui->LoadFileButtonGroup->setId(ui->tab2LoadFilef25ZoneStruct, 7);

	//ui->tab4ChangelogButton->hide();
}

void setUiColorLabels(Ui::MainWindow* ui, qreal devPixRat)
{
	QPixmap colorIcon = ColorIconDrawer::drawIcon(Qt::black, devPixRat);
	ui->ColorLable1->setPixmap(colorIcon);
	ui->ColorLable2->setPixmap(colorIcon);
	ui->ColorLable3->setPixmap(colorIcon);
	ui->ColorLable4->setPixmap(colorIcon);
	ui->ColorLable5->setPixmap(colorIcon);
	ui->ColorLable6->setPixmap(colorIcon);
	ui->ColorLable7->setPixmap(colorIcon);
	ui->ColorLable8->setPixmap(colorIcon);
	ui->ColorLable9->setPixmap(colorIcon);
	ui->ColorLable10->setPixmap(colorIcon);
	ui->ColorLable1->update();
	ui->ColorLable2->update();
	ui->ColorLable3->update();
	ui->ColorLable4->update();
	ui->ColorLable5->update();
	ui->ColorLable6->update();
	ui->ColorLable7->update();
	ui->ColorLable8->update();
	ui->ColorLable9->update();
	ui->ColorLable10->update();
}
