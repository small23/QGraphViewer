// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "mainwindow.h"

//Конструктор класса, инициализация необходимых классов,
//настройка интерфейса, восстановление предыдущх настроек
MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, settings(new SettingsKeeper(this)), ui(new Ui::MainWindow), formChangelog(new changelog(settings, this)),
	graphicsData(new GraphicsData()),
	bandData(new BandData()), surfData(new SurfData()),
	qeDosData(new QeDos()), filesSaver(new FilesSaver()), pdosParser(new PdosParser()),
	ctConvertor(new CrystalTopondConvertors()), plotParams(new PlotParameters(ui, this)),
	iconDrawer(new ColorIconDrawer()), symbols(new MathSymbols(this)),
	atomsConvert(new AtomConversion(ui, settings)), fileDiag(new FileDialogsLoad(ui, this, settings)),
	qeSurfData(new QeSurfData()), qeZoneData(new QeZoneData())
{
	QTranslator qtTranslator;
	auto a = QLibraryInfo::TranslationsPath;
	qtTranslator.load(settings->lang, QCoreApplication::applicationDirPath() + "/translations");
	qApp->installTranslator(&qtTranslator);
	//qApp->installTranslator(&qtTranslator);

	ui->setupUi(this);
	setupUiFields(ui);
	setUiButtonsGroups(ui);
	tab1GraphFont.setFamily("Times New Roman");
	tab1GraphFont.setPointSize(18);
	tab2GraphFont.setFamily("Times New Roman");
	tab2GraphFont.setPointSize(18);
	tab5GraphFont.setFamily("Times New Roman");
	tab5GraphFont.setPointSize(18);
	tab5ContourGraphFont.setFamily("Times New Roman");
	tab5ContourGraphFont.setPointSize(18);
	ui->tab1FontSize->setValue(18);


	//Generate own table
	tab5tableView = new CustomTableView(ui->groupBox_59);
	
	tab5tableView->setObjectName(QString::fromUtf8("tab5tableWidget"));
	tab5tableView->setGeometry(QRect(10, 130, 197, 155));
	QFont font9;
	font9.setFamily(QString::fromUtf8("Arial"));
	font9.setPointSize(10);
	font9.setBold(false);
	font9.setWeight(50);
	font9.setStrikeOut(false);
	font9.setKerning(true);
	tab5tableView->setFont(font9);
	tab5tableView->setWordWrap(false);
	if(QSysInfo::windowsVersion()==QSysInfo::WV_WINDOWS10){
		tab5tableView->setStyleSheet(
        "QHeaderView::section{"
            "border-top:0px solid #D8D8D8;"
            "border-left:0px solid #D8D8D8;"
            "border-right:1px solid #D8D8D8;"
            "border-bottom: 1px solid #D8D8D8;"
            "background-color:rgb(211,211,211);"
            "padding:4px;"
        "}"
        "QTableCornerButton::section{"
            "border-top:0px solid #D8D8D8;"
            "border-left:0px solid #D8D8D8;"
            "border-right:1px solid #D8D8D8;"
            "border-bottom: 1px solid #D8D8D8;"
            "background-color:white;"
        "}");
		ui->tab2PDOSNumbersTable->setStyleSheet(tab5tableView->styleSheet());
		ui->tab3ConvertedAtomsTable->setStyleSheet(tab5tableView->styleSheet());
	}

	tab5tableView->verticalHeader()->setVisible(false);
	tab5tableView->verticalHeader()->setMinimumSectionSize(0);
	tab5tableView->horizontalHeader()->setMinimumSectionSize(0);
	tab5tableView->show();

#ifdef OWN_HIGHDPI_SCALE
	//this->hide();
	getOriginBorders();
#endif

	connect(ui->tab3AtomsConvertButton,     SIGNAL(clicked()),						this,       SLOT(atomsConvertButtonPressed()));
	connect(ui->tab3AtomsSearchButton,      SIGNAL(clicked()),						this,       SLOT(atomsSearchButtonPressed()));
	connect(ui->tab3LoadFileConvertXfX,     SIGNAL(clicked()),						this,       SLOT(loadFileConvertXfXButtonPressed()));
	connect(ui->tab3LoadFilesConvertDOS,    SIGNAL(clicked()),						this,       SLOT(tab3LoadFilesConvertDosButtonPressed()));
	connect(ui->tab3SurfF25Button,          SIGNAL(clicked()),						this,       SLOT(tab3SurfF25ButtonPressed()));
	connect(ui->tab3SurfConvertButton,      SIGNAL(clicked()),						this,       SLOT(tab3SurfConvertButtonPressed()));
	connect(ui->tab3ButtonCrystalToTopond,  SIGNAL(clicked()),						this,       SLOT(tab3ButtonCrystalToTopondPressed()));
	connect(ui->tab3ButtonTopondToCrystal,  SIGNAL(clicked()),						this,       SLOT(tab3ButtonTopondToCrystalPressed()));
	connect(ui->tab2buttonDrawZoneStruct,   SIGNAL(clicked()),						this,       SLOT(tab2ButtonDrawZoneStructPressed()));
	connect(ui->ColorButtonGroup,           SIGNAL(buttonClicked(int)),				this,       SLOT(colorChangeButtonClicked(int)));
	connect(ui->DeleteButtonGroup,          SIGNAL(buttonClicked(int)),				this,       SLOT(deleteFileStringButtonClicked(int)));
	connect(ui->HelpButtonGroup,            SIGNAL(buttonClicked(int)),				this,       SLOT(helpButtonClicked(int)));
	connect(ui->LoadFileButtonGroup,        SIGNAL(buttonClicked(int)),				fileDiag,   SLOT(loadFileButtonCliked(int)));
	connect(ui->tab1LoadFilesTjMolP2,       SIGNAL(clicked()),						fileDiag,   SLOT(fileDialogMolTrajP2Load()));
	connect(ui->tab1PlotGraphic,            SIGNAL(clicked()),						this,       SLOT(plotButtonTab1Clicked()));
	connect(ui->tab1FontChangeButton,       SIGNAL(clicked()),						this,       SLOT(fontChangeButtonPressed()));
	connect(ui->tab2SpinnerLineWidth,       SIGNAL(valueChanged(QString)),			this,       SLOT(tab2UpdateParams(QString)));
	connect(ui->tab2ComboBoxLineType,       SIGNAL(currentIndexChanged(QString)),	this,       SLOT(tab2UpdateParams(QString)));
	connect(ui->tab2CheckBoxShow1,          SIGNAL(stateChanged(int)),				this,       SLOT(tab2UpdateShowLine(int)));
	connect(ui->tab2SpinnerLineMultiplier,  SIGNAL(valueChanged(QString)),			this,       SLOT(tab2UpdateParams(QString)));
	connect(ui->tab2ComboBoxLineSelector,   SIGNAL(currentIndexChanged(int)),		this,       SLOT(tab2ComboBoxLineSelectorIndexChanged(int)));
	connect(ui->tab2ButtonDrawDOS,          SIGNAL(clicked()),						this,       SLOT(tab2ButtonDrawDosPressed()));
	connect(ui->tab2BushButtonSetFont,      SIGNAL(clicked()),						this,       SLOT(tab2BushButtonSetFontPressed()));
	connect(ui->tab4QtAbout,                SIGNAL(clicked()),						this,       SLOT(tab4QtAbout()));
	connect(ui->tab2LoadFilef25DOSS,        SIGNAL(clicked()),						this,       SLOT(tab2LoadFilef25DossPressed()));
	connect(ui->tab4LicenceMIT,             SIGNAL(clicked()),						this,       SLOT(tab4LicenceMit()));
	connect(ui->tab2PushButtonPDOSLoad,     SIGNAL(clicked()),						this,       SLOT(tab2PushButtonPdosLoadPressed()));
	connect(ui->tab4ChangelogButton,        SIGNAL(clicked()),						this,       SLOT(tab4Changelog()));
	connect(ui->tab5SpinnerLineWidth,		  SIGNAL(valueChanged(QString)),			this,       SLOT(tab5UpdateParams(QString)));
	connect(ui->tab5ComboBoxLineType,		  SIGNAL(currentIndexChanged(QString)),	this,       SLOT(tab5UpdateParams(QString)));
	connect(ui->tab5CheckBoxShow1,          SIGNAL(stateChanged(int)),				this,       SLOT(tab5UpdateShowLine(int)));
	connect(ui->tab5SpinnerLineMultiplier,  SIGNAL(valueChanged(QString)),			this,       SLOT(tab5UpdateParams(QString)));
	connect(ui->tab5ComboBoxLineSelector,   SIGNAL(currentIndexChanged(int)),		this,       SLOT(tab5ComboBoxLineSelectorIndexChanged(int)));
	connect(ui->tab5BushButtonSetFont,	  SIGNAL(clicked()),						this,       SLOT(tab5BushButtonSetFontPressed()));
	connect(ui->tab5LoadFilefQEDOSS,		  SIGNAL(clicked()),						this,       SLOT(tab5LoadFileDossPressed()));
	connect(ui->tab5ButtonDrawDOS,		  SIGNAL(clicked()),						this,       SLOT(tab5DrawDosPressed()));
	connect(ui->tab5LoadFilecomboBox,		  SIGNAL(currentIndexChanged(int)),		this,       SLOT(tab5UpdateParamsFile(int)));
	connect(ui->tab5LanguageChange,		  SIGNAL(clicked()),                      this,       SLOT(tab5LanguageChanged()));
	connect(ui->tab5LoadSurfDatButton,      SIGNAL(clicked()),                      this,       SLOT(tab5LoadSurfConvButtonPressed()));
	connect(ui->tab5LoadQEDen,              SIGNAL(clicked()),                      this,       SLOT(tab5LoadQEDenButtonPressed()));
	connect(ui->tab5PlotGraphic,            SIGNAL(clicked()),                      this,       SLOT(tab5PlotGraphicButtonPressed()));
	connect(ui->tab5FontChangeButton,       SIGNAL(clicked()),                      this,       SLOT(tab5PushButtonSetFontContourPressed()));
	connect(ui->tab5_loadQeBand,		      SIGNAL(clicked()),                      this,       SLOT(tab5LoadQeBandButtonPressed()));
	connect(ui->tab5buttonDrawZoneStruct,   SIGNAL(clicked()),                      this,       SLOT(tab5DrawZoneButtonPressed()));

	this->setStatusBar(nullptr);
	this->setFixedSize(this->size());
	this->setWindowTitle("QGraphViewer");

#ifdef OWN_HIGHDPI_SCALE

	auto screenList = QGuiApplication::screens();
	for (auto screen : screenList)
	{
		//connect(screen, SIGNAL(logicalDotsPerInchChanged(qreal)), this, SLOT(dotsPerInchChanged(qreal)));
	}

	resizeWidgets(QGuiApplication::screens().at(0)->logicalDotsPerInch() / 96.0);
#endif

	QSize targetWindowSize = this->size();
	QRect rec = QGuiApplication::screens().at(0)->geometry();
	rec.setTop((rec.height() - targetWindowSize.height()) / 2);
	rec.setLeft((rec.width() - targetWindowSize.width()) / 2);
	rec.setWidth(this->size().width());
	rec.setHeight(this->size().height());
	this->setGeometry(rec);
	this->show();
	qreal displayScale = this->window()->windowHandle()->devicePixelRatio();
#ifdef OWN_HIGHDPI_SCALE
	QScreen* pScreen = QGuiApplication::screenAt(this->mapToGlobal({ this->width() / 2,this->height() / 2 }));
	displayScale = pScreen->logicalDotsPerInch() / 96.0;
#endif
	connect(this->window()->windowHandle(), SIGNAL(screenChanged(QScreen*)), this, SLOT(screenChanged(QScreen*)));
	setUiColorLabels(ui, displayScale);
	imageInit(ui, displayScale);

#ifdef OWN_HIGHDPI_SCALE
	SetTab5TableCellSize(displayScale);
	tableInit(ui, displayScale);
#endif
	//Корректировочный коэффициент масштабирования
	//графиков на дисплеях с масштабом !=100%
    //TODO Remove
	plotParams->drawRes = settings->scaleRes;
	plotParams->drawQuality = settings->quality;
	plotParams->drawScale = settings->scale;
	plotParams->preferFormat = settings->imageType;
	plotParams->displayScale = displayScale;
}

void MainWindow::SetTab5TableCellSize(qreal scale)
{
	QFontMetrics fontKpoints(tab5tableView->font());
	tab5tableView->verticalHeader()->setDefaultSectionSize(fontKpoints.height() * 1.5);
	tab5tableView->horizontalHeader()->setMinimumHeight(fontKpoints.height() * 1.5);
	tab5tableView->horizontalHeader()->setMaximumHeight(fontKpoints.height() * 1.5);
	//QRect g = tab5tableView->verticalScrollBar()->geometry();
	int width = tab5tableView->width();
	width -= 18 * (scale); //TODO FIND WAY TO GET SCROLL SIZE!!!!!!!!!!!!!
	tab5tableView->setColumnWidth(0, width / 4);
	tab5tableView->setColumnWidth(1, width / 4);
	tab5tableView->setColumnWidth(2, width / 4);
	tab5tableView->setColumnWidth(3, width / 4);
	
}

#ifdef OWN_HIGHDPI_SCALE

void MainWindow::resizeEvent(QResizeEvent* event)
{
	QScreen* screen = QGuiApplication::screenAt(this->mapToGlobal({ this->width() / 2,this->height() / 2 }));
	//screenChanged(pScreen);
	resizeWidgets(screen->logicalDotsPerInch() / 96.0);
	imageInit(ui, screen->logicalDotsPerInch() / 96.0);
	tableInit(ui, screen->logicalDotsPerInch() / 96.0);
	for (int i = 1; i < 11; i++)
	{
		setColotLabelById(i, screen->logicalDotsPerInch() / 96.0);
	}
	SetTab5TableCellSize(screen->logicalDotsPerInch() / 96.0);
	QMainWindow::resizeEvent(event);
	
}

void MainWindow::dotsPerInchChanged(qreal dpi)
{
	QScreen* pScreen = QGuiApplication::screenAt(this->mapToGlobal({ this->width() / 2,this->height() / 2 }));
	screenChanged(pScreen);
}

void MainWindow::getOriginBorders()
{
	QLayout* ql = this->layout();

	if (ql == NULL)
		return;

	QWidget* pw = ql->parentWidget();

	if (pw == NULL)
		return;

	QString widgetClass;
	QString widgetName;
	widgetParams* params;
	foreach(QWidget * w, pw->findChildren<QWidget*>())
	{
		widgetClass = w->metaObject()->className();
		widgetName = w->objectName();
		if (widgetClass == "QWidget" || widgetName.count() == 0 || widgetName.contains("qt_")) // Skip all non-user elements
			continue;
		widgetParams* params = new widgetParams();
		params->pos = w->pos();
		params->geom = w->geometry();
		params->minSize = w->minimumSize();
		params->maxSize = w->maximumSize();
		windgetPramsList.append(params);
		hashWidgets.insert(w->objectName(), windgetPramsList.count());
	}
}

void MainWindow::resizeWidgets(qreal mratio) // https://stackoverflow.com/questions/39823918/how-to-approach-development-of-new-qt-5-7-high-dpi-per-monitor-dpi-aware-applic
{
	QLayout* ql = this->layout();

	if (ql == nullptr)
		return;

	QWidget* pw = ql->parentWidget();

	if (pw == nullptr)
		return;
#ifdef DEBUG_PAINT
	QString wName = "";
	int counter = 0;
#endif
	QString widgetClass;
	QString widgetName;
	widgetParams* params;
	foreach(QWidget * w, pw->findChildren<QWidget*>())
	{
		widgetClass = w->metaObject()->className();
		widgetName = w->objectName();

		if (widgetClass == "QWidget" || widgetName.count()==0 || widgetName.contains("qt_")) // Skip all non-user elements
			continue;

		int i = hashWidgets.value(w->objectName());
		if (i>0)
		{
			params = windgetPramsList[i - 1];
			QPoint pos = params->pos * mratio;
	
			w->resize(params->geom.width() * mratio, params->geom.height() * mratio);
			w->move(pos);
#ifdef DEBUG_PAINT
			counter++;
			w->update();
			w->repaint();
			QApplication::processEvents();
#endif
		}
		
	}
	
	if (this->maximumSize().height() > ui->tabWidget->height())
	{
		this->setMinimumSize(ui->tabWidget->width(), ui->tabWidget->height());
		this->resize(ui->tabWidget->width(), ui->tabWidget->height());
		this->setMaximumSize(ui->tabWidget->width(), ui->tabWidget->height());
	}
	else
	{
		this->setMaximumSize(ui->tabWidget->width(), ui->tabWidget->height());
		this->resize(ui->tabWidget->width(), ui->tabWidget->height());
		this->setMinimumSize(ui->tabWidget->width(), ui->tabWidget->height());
	}
}

void MainWindow::checkParent(QWidget* wdg, bool & have, QString name)
{
	auto par = wdg->parentWidget();
	if (par!=nullptr)
	{
		checkParent(par, have, name);
	}
	if (wdg->objectName() == name)
		have = true;
}

#endif

MainWindow::~MainWindow()
{
	settings->saveSettings();
	delete ui;
}

void MainWindow::showPictureSettings()
{
	if (formPictureSettings!=nullptr)
	{
		formPictureSettings->close();
		delete formPictureSettings;
	}
	formPictureSettings = new PictureSettings(plotParams, settings,this);
	formPictureSettings->setModal(true);
	formPictureSettings->exec();
}

void MainWindow::colorChangeButtonClicked(const int id) const
{
	QColorDialog colorPickerMenu;
	const QRect windowLocation = geometry();
	colorPickerMenu.setGeometry(windowLocation.x() + 100, windowLocation.y() + 50, 522, 393);
	colorPickerMenu.exec();
	const QColor choosenColor = colorPickerMenu.selectedColor();
	if (!choosenColor.isValid()) return;
#ifdef OWN_HIGHDPI_SCALE
	const QPixmap colorIcon = ColorIconDrawer::drawIcon(choosenColor, QGuiApplication::screens().at(0)->logicalDotsPerInch() / 96.0);
#else
	const QPixmap colorIcon = ColorIconDrawer::drawIcon(choosenColor, this->window()->windowHandle()->devicePixelRatio());
#endif
	const QString colorLabelName = QString("ColorLable%1").arg(id);
	QLabel* colorLabel = findChild<QLabel*>(colorLabelName);
	if (colorLabel != nullptr)
	{
		//LinesParams[id-1].color=choosenColor;
		plotParams->updateColors(id, choosenColor);
		QIcon redIcon(colorIcon);
		colorLabel->setPixmap(colorIcon);
		colorLabel->update();
	}
}

void MainWindow::setColotLabelById(const int id, qreal scale) const
{
	
	const QString colorLabelName = QString("ColorLable%1").arg(id);
	QLabel* colorLabel = findChild<QLabel*>(colorLabelName);
	if (colorLabel != nullptr)
	{
		QColor choosenColor;
		if (id < 7)
			choosenColor = plotParams->tab1PlotParams[id - 1].color;
		else if (id == 8)
		{
			const int workingLine = ui->tab2ComboBoxLineSelector->currentIndex();
			choosenColor = plotParams->tab2PlotParams->data()[workingLine].color;
		}
		else if (id == 7)
			choosenColor = plotParams->tab2FermiLevel;
		else if (id == 9)
		{
			int workingLine = ui->tab5ComboBoxLineSelector->currentIndex();
			for (int i = 0; i < ui->tab5LoadFilecomboBox->currentIndex(); i++)
				workingLine += plotParams->tab5LinesCounter->at(i);
			choosenColor = plotParams->tab5PlotParams->data()[workingLine].color;
		}
		else if (id == 10)
			choosenColor = plotParams->tab5FermiLevelColor;
		const QPixmap colorIcon = ColorIconDrawer::drawIcon(choosenColor, scale);
		colorLabel->setPixmap(colorIcon);
		colorLabel->update();
	}
}

void MainWindow::deleteFileStringButtonClicked(const int id) const
{
	QString lineName;
	if (id < 7)
		lineName = QString("tab1FileLine%1").arg(id);
	else if (id == 8 || id == 7)
		lineName = QString("tab2FileLine%1").arg(id - 6);
	else if (id > 8)
	{
		if (id!=10)
			lineName = QString("tab5FileLine%1").arg(id - 8);
		else
		{
			disconnect(ui->tab5ComboBoxLineSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(tab5ComboBoxLineSelectorIndexChanged(int)));
			disconnect(ui->tab5LoadFilecomboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(tab5UpdateParamsFile(int)));
			ui->tab5LoadFilecomboBox->clear();
			ui->tab5LoadFilecomboBox->setToolTip("");
			ui->tab5ComboBoxLineSelector->clear();
			plotParams->tab5SetCountOfLines(1);
			ui->tab5ComboBoxLineSelector->addItem("1");
			ui->tab5ComboBoxLineSelector->setCurrentIndex(0);
			connect(ui->tab5ComboBoxLineSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(tab5ComboBoxLineSelectorIndexChanged(int)));
			connect(ui->tab5LoadFilecomboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(tab5UpdateParamsFile(int)));
		}
	}
		
	QLineEdit* lineEdit = findChild<QLineEdit*>(lineName);
	if (lineEdit != nullptr)
	{
		lineEdit->clear();
		lineEdit->setToolTip("");
		if (id == 8)
		{
			ui->tab2ComboBoxLineSelector->clear();
			plotParams->tab2SetCountOfLines(1);
			ui->tab2ComboBoxLineSelector->addItem("1");
			ui->tab2ComboBoxLineSelector->setCurrentIndex(0);
			if (ui->tab2CheckBoxShow1->isChecked())
				ui->tab2ComboBoxLineSelector->setItemData(ui->tab2ComboBoxLineSelector->currentIndex(), QBrush(MenuSelectedGraph), Qt::ForegroundRole); //TextColorRole
			else
				ui->tab2ComboBoxLineSelector->setItemData(ui->tab2ComboBoxLineSelector->currentIndex(), QBrush(Qt::black), Qt::ForegroundRole);
		}
		if (id == 10)
		{
			ui->tab5ComboBoxLineSelector->clear();
			plotParams->tab5SetCountOfLines(1);
			ui->tab5ComboBoxLineSelector->addItem("1");
			ui->tab5ComboBoxLineSelector->setCurrentIndex(0);
		}
	}
}

void MainWindow::helpButtonClicked(const int id)
{
	const QRect windowLocation = geometry();
	if (id == 2)
	{
		HelpMatrixWidget* a = new HelpMatrixWidget(ui, windowLocation, QApplication::desktop()->screenGeometry());
		a->installEventFilter(a);
	}
	else
	{
		const QString helpFile = QString(":resource/help/HELP%1.png").arg(id);
		const QPixmap helpPixmap = QPixmap(helpFile);
		new HelpWindow(helpPixmap, windowLocation, QApplication::desktop()->screenGeometry());
	}
}

void MainWindow::plotButtonTab1Clicked()
{
	//Проверки на безопастность и наличие файлов
	if (ui->tab1FileLine1->text()+ ui->tab1FileLine2->text()+ ui->tab1FileLine3->text()+ ui->tab1FileLine4->text()+ ui->tab1FileLine5->text()+ ui->tab1FileLine6->text() == "")
	{
		QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_NoFilesToDraw);
		return;
	}

	if (ui->tab1FileLine1->text() + ui->tab1FileLine2->text() + ui->tab1FileLine3->text() + ui->tab1FileLine4->text() + ui->tab1FileLine6->text() == "" && ui->tab1FileLine5->text()!="")
	{
		QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_NoDatafiles);
		return;
	}

	if (ui->tab1FileLine1->text() + ui->tab1FileLine2->text() + ui->tab1FileLine3->text() != "" &&
		ui->tab1FileLine5->text() =="" && ui->tab1FileLine4->text() + ui->tab1FileLine6->text() != "")
	{
		QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_NoOutpFileWithTransMatrix);
	}

	//Сохранение путей до файлов в единый массив для передачи в парсер
	QList<QString> fields;
	fields.append(ui->tab1FileLine1->text());
	fields.append(ui->tab1FileLine2->text());
	fields.append(ui->tab1FileLine3->text());
	fields.append(ui->tab1FileLine5->text());
	plotParams->updatePlotParams(1);
	QList<QString>* content = new QList<QString>();

	const int success = graphicsData->getAndParseMainData(fields, ui->tab1AtomsCutOff->text().toDouble());
	if (success != 1)
	{
		switch (success)
		{
		case 0:
			QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_CorruptDataOutp);
			break;
		case -1:
			QMessageBox::warning(this, STR_ErrorTitle_ParsingError,STR_ErrorMessage_CorruptDataTrajgrad);
			break;
		case -2:
			QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_CorruptDataMolgraph);
			break;
		case -3:
			QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_CorruptDataMolgraph2);
			break;
		default:
			break;
		}

		graphicsData->clear();
		delete content;
		return;
	}
	
	if(fields[0]+ fields[1]+ fields[2]!="" && fields[3]=="" && ui->tab1FileLine6->text() == "" && ui->tab1FileLine4->text() == "")
	{
		QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_NoOutpFileWithTransMatrixStopDraw);
		delete content;
		return;
	}

	
	if (ui->tab1FileLine6->text() != "")
	{
		readFileFromFs(ui->tab1FileLine6->text(), content);
		bandData->parseData(content, ui->tab1uhf->isChecked());
	}
	else
		bandData->clear();

	if (ui->tab1FileLine4->text() != "")
	{
		readFileFromFs(ui->tab1FileLine4->text(), content);
		surfData->parseData(content);
	}
	else
		surfData->clear();

	//Вызов отрисовки в зависимости от параметров выходных файлов
	delete content;
	tab1GraphFont.setPointSize(ui->tab1FontSize->value());
	if (ui->tab1FileLine4->text() != "" || ui->tab1FileLine5->text() != "" || ui->tab1FileLine6->text() != "")
	{
		if (plotParams->tab1PlotParams[6].show)
		{
			if (bandData->outputMAPN.count() > 0)
			{
				for (int i = 0; i < bandData->outputMAPN.count(); i++)
				{
					(new BasicGraph(settings, STR_GraphTitle_PlotDefaultName, plotParams, tab1GraphFont, this))->draw( ui->tab1ShowAxis->isChecked(),
							 i, ui->tab1uhf->isChecked(), graphicsData, surfData, bandData, ui->tab1ComboBoxRotate->currentIndex() * 90);
				}
			}
			else
				(new BasicGraph(settings, STR_GraphTitle_PlotDefaultName, plotParams, tab1GraphFont, this))->draw(ui->tab1ShowAxis->isChecked(),
						 0, ui->tab1uhf->isChecked(), graphicsData, surfData, bandData, ui->tab1ComboBoxRotate->currentIndex() * 90);
		}
		else
			(new BasicGraph(settings, STR_GraphTitle_PlotDefaultName, plotParams, tab1GraphFont, this))->draw(ui->tab1ShowAxis->isChecked(),
					 0, ui->tab1uhf->isChecked(), graphicsData, surfData, bandData, ui->tab1ComboBoxRotate->currentIndex() * 90);
	}

}

void MainWindow::fontChangeButtonPressed() {
	bool ok;
	QFontDialog test;
	const auto windowLocation = geometry();
	test.setGeometry(windowLocation.x() + 100, windowLocation.y() + 50, 480, 360);
	const QFont font = QFontDialog::getFont(&ok, tab1GraphFont);//QFontDialog::getFont(&ok, tab1GraphFont, this);
	if (ok) {
		tab1GraphFont = font;
		ui->tab1FontSize->setValue(font.pointSize());
	}
	else {

	}
}

void MainWindow::atomsConvertButtonPressed() const
{
	atomsConvert->convertAtoms();
}

void MainWindow::atomsSearchButtonPressed() const
{
	atomsConvert->convertAndSearchAtoms();
}

void MainWindow::loadFileConvertXfXButtonPressed()
{
	QList<QString>* content = new QList<QString>();
	const QString fileName = QFileDialog::getOpenFileName(this, STR_Dialog_OpenFile, settings->getLastPath(),
														  "*.f25 (*.f25);;All Files (*)");
	if (fileName != "")
	{
		const QFileInfo fileinfo(fileName);
		settings->updatePath(fileinfo.absolutePath());
		readFileFromFs(fileName, content);
	}
	else
	{
		delete content;
		return;
	}

	bandData->parseData(content, ui->tab3uhfZoneStruct);
	delete content;
	if (bandData->outputBAND.count() > 0)
	{
		const bool success = filesSaver->saveBandData(fileName, bandData, ui->tab3ZoneStructYMin->text().toDouble(), ui->tab3ZoneStructYMax->text().toDouble(), ui->tab3uhfZoneStruct->isChecked());
		if (success == false)
		{
			QMessageBox::critical(this, STR_ErrorTitle_SaveError, STR_ErrorMessage_CantOpenFileForWrite.arg(filesSaver->errorData.ErrorFile));//QMessageBox::critical(this, STR_ErrorTitle_SaveError, tr("'") + filesSaver->errorData.ErrorFile + tr("' не удается открыть для записи!"));
			return;
		}
		QMessageBox::information(this, STR_MessageBoxTitle_DataProcessed, STR_MessageBoxMessage_DataProcessedAndSaved);
	}
	else
		QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_NoNecessaryDataInFile);
}

void MainWindow::tab3LoadFilesConvertDosButtonPressed()
{
	QList<QString>* content = new QList<QString>();
	const QString fileName = QFileDialog::getOpenFileName(this,
														  STR_Dialog_OpenFile, settings->getLastPath(),
														  "*.f25 (*.f25);;All Files (*)");
	if (fileName != "")
	{
		const QFileInfo fileinfo(fileName);
		settings->updatePath(fileinfo.absolutePath());
		readFileFromFs(fileName, content);
	}
	else
	{
		delete content;
		return;
	}

	bandData->parseData(content);
	delete content;
	if (bandData->outputCOHP.count() > 0 || bandData->outputCOOP.count() > 0 || bandData->outputDOSS.count() > 0)
	{
		const bool success = filesSaver->saveDosData(fileName, bandData);
		if (success == false)
		{
			QMessageBox::critical(this, STR_ErrorTitle_SaveError, STR_ErrorMessage_CantOpenFileForWrite.arg(filesSaver->errorData.ErrorFile));
			return;
		}
		QMessageBox::information(this, STR_MessageBoxTitle_DataProcessed, STR_MessageBoxMessage_DataProcessedAndSaved);
	}
	else
		QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_NoNecessaryDataInFile);
}

void MainWindow::tab3SurfF25ButtonPressed()
{
	QList<QString>* content = new QList<QString>();
	const QString fileName = QFileDialog::getOpenFileName(this,
														   STR_Dialog_OpenFile, settings->getLastPath(),
														   "*.f25 (*.f25);;All Files (*)");
	if (fileName != "")
	{
		const QFileInfo fileInfo(fileName);
		settings->updatePath(fileInfo.absolutePath());
		readFileFromFs(fileName, content);
	}
	else
	{
		delete content;
		return;
	}

	bandData->parseData(content, ui->tab3uhff25->isChecked());
	delete content;
	if (bandData->outputMAPN.count() > 0)
	{
		const bool success = filesSaver->saveMapnData(fileName, bandData, ui->tab3SurfRotationSelector->currentIndex() * 90);
		if (success == false)
		{
			QMessageBox::critical(this, STR_ErrorTitle_SaveError, STR_ErrorMessage_CantOpenFileForWrite.arg(filesSaver->errorData.ErrorFile));
			return;
		}
		QMessageBox::information(this, STR_MessageBoxTitle_DataProcessed, STR_MessageBoxMessage_DataProcessedAndSaved);
	}
	else
		QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_NoNecessaryDataInFile);
}

void MainWindow::tab3SurfConvertButtonPressed()
{
	QList<QString>* content = new QList<QString>();
	const QString fileName = QFileDialog::getOpenFileName(this,
														  STR_Dialog_OpenFile, settings->getLastPath(),
														  "*.dat (*.dat);;All Files (*)");
	if (fileName != "")
	{
		const QFileInfo fileinfo(fileName);
		settings->updatePath(fileinfo.absolutePath());
		readFileFromFs(fileName, content);
	}
	else
	{
		delete content;
		return;
	}

	surfData->parseData(content);
	delete content;
	if (surfData->oF.count() > 0)
	{
		surfData->rotateData(ui->tab3SurfRotationSelector->currentIndex() * 90);
		QProgressDialog progressBar;
		progressBar.setValue(0);
		progressBar.setRange(0, 1);
		progressBar.show();

		QString path;
		QStringList pathTemp = fileName.split("/");


		for (int i = 0; i < pathTemp.count() - 1; i++)
			path += pathTemp.at(i) + "/";
		path += "TOPOND";
		const QDir dir(path);
		if (!dir.exists())
			dir.mkpath(".");
		const QString pathFull = path + "/" + pathTemp[pathTemp.count() - 1].mid(4, 4) + "-" + QString::number(
			ui->tab3SurfRotationSelector->currentIndex() * 90) + ".xlsx";
		QXlsx::Document xlsx;
		for (int j = 0; j < surfData->oF.count(); j++)
		{
			xlsx.write(j + 1, 1, surfData->oRepeatY[j]);
			xlsx.write(j + 1, 2, surfData->oRepeatX[j]);
			xlsx.write(j + 1, 3, surfData->oF[j]);
		}
		QApplication::processEvents();
		const bool success = xlsx.saveAs(pathFull); // save the document as 'Test.xlsx'
		if (success != true)
		{
			progressBar.close();
			QMessageBox::critical(this, STR_ErrorTitle_SaveError, STR_ErrorMessage_CantOpenFileForWrite.arg(pathFull));
			return;
		}
		progressBar.close();
		QMessageBox::information(this, STR_MessageBoxTitle_DataProcessed, STR_MessageBoxMessage_DataProcessedAndSaved);
	}
	else
		QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_NoNecessaryDataInFile);
}

void MainWindow::tab3ButtonCrystalToTopondPressed()
{
	QList<QString>* content = new QList<QString>();
	const QString fileName = QFileDialog::getOpenFileName(this,
														  STR_Dialog_OpenFile, settings->getLastPath(),
														  "Output file (*.outp);;All Files (*)");
	if (fileName != "")
	{
		const QFileInfo fileinfo(fileName);
		settings->updatePath(fileinfo.absolutePath());
		readFileFromFs(fileName, content);
	}
	else
	{
		delete content;
		return;
	}

	ctConvertor->convertCrystalToTopond(content);

	delete content;

	if (ctConvertor->output != "")
	{
		QString path;
		QString name;
		QStringList pathTemp = fileName.split("/");

		for (int i = 0; i < pathTemp.count() - 1; i++)
			path += pathTemp.at(i) + "/";
		pathTemp = pathTemp.at(pathTemp.count() - 1).split(".");
		path = path + pathTemp.at(0) + "_ToTOPOND.d3";
		QFile file(path);
		if (file.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			QTextStream stream(&file);
			stream << ctConvertor->output;
			file.close();
		}
		else
		{
			QMessageBox::critical(this, STR_ErrorTitle_SaveError, STR_ErrorMessage_CantOpenFileForWrite.arg(path));
			return;
		}
		QMessageBox::information(this, STR_MessageBoxTitle_DataProcessed, STR_MessageBoxMessage_DataProcessedAndSaved);
	}
	else
		QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_NoNecessaryDataInFile);
}

void MainWindow::tab3ButtonTopondToCrystalPressed()
{
	QList<QString>* content = new QList<QString>();
	const QString fileName = QFileDialog::getOpenFileName(this,
														  STR_Dialog_OpenFile, settings->getLastPath(),
														  "Output file (*.outp);;All Files (*)");
	if (fileName != "")
	{
		const QFileInfo fileinfo(fileName);
		settings->updatePath(fileinfo.absolutePath());
		readFileFromFs(fileName, content);
	}
	else
	{
		delete content;
		return;
	}
	ctConvertor->convertTopondToCrystal(content);

	delete content;

	if (ctConvertor->output != "")
	{
		QString path;
		QString name;
		QStringList pathTemp = fileName.split("/");

		for (int i = 0; i < pathTemp.count() - 1; i++)
			path += pathTemp.at(i) + "/";
		pathTemp = pathTemp.at(pathTemp.count() - 1).split(".");
		path = path + pathTemp.at(0) + "_ToCRYSTAL.d3";
		QFile file(path);
		if (file.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			// We're going to streaming text to the file
			QTextStream stream(&file);
			stream << ctConvertor->output;
			file.close();
		}
		else
		{
			QMessageBox::critical(this, STR_ErrorTitle_SaveError, STR_ErrorMessage_CantOpenFileForWrite.arg(path));
			return;
		}
		QMessageBox::information(this, STR_MessageBoxTitle_DataProcessed, STR_MessageBoxMessage_DataProcessedAndSaved);
	}
	else
		QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_NoNecessaryDataInFile);
}

void MainWindow::tab2ButtonDrawZoneStructPressed()
{
	QList<QString>* content = new QList<QString>();
	if (ui->tab2FileLine1->text() != "")
	{
		{
			const QFileInfo fileinfo(ui->tab2FileLine1->text());
			settings->updatePath(fileinfo.absolutePath());
			readFileFromFs(ui->tab2FileLine1->text(), content);
		}
	}
	else
	{
		delete content;
		QMessageBox::warning(this, STR_ErrorTitle_LoadingError, STR_ErrorMessage_NoFileToDraw);
		return;
	}
	bandData->parseData(content);

	delete content;

	plotParams->updatePlotParams(2);
	ui->tab2ComboBoxLineSelector->setCurrentIndex(0);
	ui->tab2ComboBoxLineSelector->update();
	if (bandData->outputBAND.count() > 0)
	{
		double numbersToBuild[2];

		if (plotParams->tab2Uhf)
		{
			for (int i = 0; i < 2; i++)
			{
				numbersToBuild[0] = bandData->oXBand[bandData->oXBand.size() / 2 * i];
				numbersToBuild[1] = bandData->oXBand[bandData->oXBand.size() / 2 * (i + 1) - 1];
				(new ZoneGraph(settings, QString((STR_GraphTitle_ZoneStruct.toStdString() + " " + std::to_string(i + 1)).c_str()), plotParams, tab2GraphFont, this))->
					draw(bandData, ui->tab2ZoneStructYMin->text().toDouble(),
						ui->tab2ZoneStructYMax->text().toDouble(), ui->tab2LineKPoints->text(),
						numbersToBuild, symbols);
			}
		}
		else
		{
			numbersToBuild[0] = 0;
			numbersToBuild[1] = bandData->oXBand[bandData->oXBand.size() - 1];
			(new ZoneGraph(settings, STR_GraphTitle_ZoneStruct, plotParams, tab2GraphFont, this))->
				draw(bandData, ui->tab2ZoneStructYMin->text().toDouble(),
					ui->tab2ZoneStructYMax->text().toDouble(), ui->tab2LineKPoints->text(),
					numbersToBuild, symbols);
		}
	}
	else
		QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_NoNecessaryDataInFile);
}

void MainWindow::tab2UpdateParams(QString i) const
{
	plotParams->updatePlotParams(2);
}

void MainWindow::tab2UpdateShowLine(int i) const
{
	plotParams->updatePlotParams(2);
	if (ui->tab2CheckBoxShow1->isChecked())
		ui->tab2ComboBoxLineSelector->setItemData(ui->tab2ComboBoxLineSelector->currentIndex(), QBrush(MenuSelectedGraph), Qt::ForegroundRole); //TextColorRole
	else
		ui->tab2ComboBoxLineSelector->setItemData(ui->tab2ComboBoxLineSelector->currentIndex(), QBrush(Qt::black), Qt::ForegroundRole);
}

void MainWindow::tab2LoadFilef25DossPressed()
{
	const QString fileName = QFileDialog::getOpenFileName(this,
														  STR_Dialog_OpenFile, settings->getLastPath(),
														  tr("f25 files (*.f25);;All Files (*)"));
	if (fileName != "")
	{
		QList<QString>* content = new QList<QString>();
		readFileFromFs(fileName, content);
		const QFileInfo fileinfo(fileName);
		settings->updatePath(fileinfo.absolutePath());
		ui->tab2FileLine2->setText(fileName);
		ui->tab2FileLine2->setToolTip(fileName);
		QVector<int> count = bandData->countData(content);
		if (count[0] > 0 || count[1] > 0 || count[2] > 0)
		{
			const int sum = count[0] + count[1] + count[2];
			ui->tab2ComboBoxLineSelector->clear();
			plotParams->tab2SetCountOfLines(sum);
			int internalCounter = 0;
			for (int i = 0; i < count[0]; i++)
				ui->tab2ComboBoxLineSelector->addItem(QString::number(i + 1) + ": COHP");
			for (int i = 0; i < count[1]; i++)
				ui->tab2ComboBoxLineSelector->addItem(QString::number(i + 1) + ": COOP");
			for (int i = 0; i < count[2]; i++)
				ui->tab2ComboBoxLineSelector->addItem(QString::number(i + 1) + ": DOS");
			ui->tab2ComboBoxLineSelector->setCurrentIndex(0);

			for (int i=0; i< sum; i++)
			{
				if (plotParams->tab2PlotParams->at(i).show)
				{
					ui->tab2ComboBoxLineSelector->setItemData(i, QBrush(MenuSelectedGraph), Qt::ForegroundRole);
				}
				else
				{
					ui->tab2ComboBoxLineSelector->setItemData(i, QBrush(Qt::black), Qt::ForegroundRole);
				}
			}
		}
		else
		{
			ui->tab2ComboBoxLineSelector->clear();
			plotParams->tab2SetCountOfLines(1);
			ui->tab2ComboBoxLineSelector->addItem("1");
			ui->tab2ComboBoxLineSelector->setCurrentIndex(0);
		}
		delete content;
	}
}

void MainWindow::tab2ComboBoxLineSelectorIndexChanged(const int selected) const
{
	if (selected != -1)
	{
		disconnect(ui->tab2SpinnerLineWidth, SIGNAL(valueChanged(QString)), this, SLOT(tab2UpdateParams(QString)));
		disconnect(ui->tab2ComboBoxLineType, SIGNAL(currentIndexChanged(QString)), this, SLOT(tab2UpdateParams(QString)));
		disconnect(ui->tab2CheckBoxShow1, SIGNAL(stateChanged(int)), this, SLOT(tab2UpdateShowLine(int)));
		disconnect(ui->tab2SpinnerLineMultiplier, SIGNAL(valueChanged(QString)), this, SLOT(tab2UpdateParams(QString)));
		ui->tab2SpinnerLineWidth->setValue(plotParams->tab2PlotParams->at(selected).width);
		ui->tab2SpinnerLineWidth->update();
		ui->ColorLable8->setPixmap(ColorIconDrawer::drawIcon(plotParams->tab2PlotParams->at(selected).color, this->window()->windowHandle()->devicePixelRatio()));
		ui->ColorLable8->update();
		ui->tab2CheckBoxShow1->setChecked(plotParams->tab2PlotParams->at(selected).show);
		ui->tab2CheckBoxShow1->update();
		ui->tab2ComboBoxLineType->setCurrentIndex(plotParams->tab2PlotParams->at(selected).styleId);
		ui->tab2ComboBoxLineType->update();
		ui->tab2SpinnerLineMultiplier->setValue(plotParams->tab2PlotParams->at(selected).multiplier);
		ui->tab2SpinnerLineMultiplier->update();
		connect(ui->tab2SpinnerLineWidth, SIGNAL(valueChanged(QString)), this, SLOT(tab2UpdateParams(QString)));
		connect(ui->tab2ComboBoxLineType, SIGNAL(currentIndexChanged(QString)), this, SLOT(tab2UpdateParams(QString)));
		connect(ui->tab2CheckBoxShow1, SIGNAL(stateChanged(int)), this, SLOT(tab2UpdateShowLine(int)));
		connect(ui->tab2SpinnerLineMultiplier, SIGNAL(valueChanged(QString)), this, SLOT(tab2UpdateParams(QString)));
	}
}

void MainWindow::tab2ButtonDrawDosPressed()
{
	QList<QString>* content = new QList<QString>();
	if (ui->tab2FileLine2->text() != "")
	{
		readFileFromFs(ui->tab2FileLine2->text(), content);
		const QFileInfo fileinfo(ui->tab2FileLine2->text());
		settings->updatePath(fileinfo.absolutePath());
	}
	else
	{
		delete content;
		QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_NoFileToDraw);
		return;
	}

	bandData->parseData(content);
	plotParams->updatePlotParams(2);
	double borders[4] = { ui->tab2DOSXMin->text().toDouble(),ui->tab2DOSXMax->text().toDouble(),ui->tab2DOSYMin->text().toDouble(),ui->tab2DOSYMax->text().toDouble() };
	if (bandData->outputCOHP.count() > 0 || bandData->outputDOSS.count() > 0 || bandData->outputCOOP.count() > 0)
		//new DOSGraphBuilder(bandData, borders, plotParams, tab2GraphFont, ui->tab2ComboBoxDosRotate->currentIndex(), settings, symbols,ui->tab2ComboBoxLineSelector->currentIndex(), this);
		(new DosGraph(settings, STR_GraphTitle_PlotDefaultName, plotParams, tab2GraphFont, this))->draw(bandData, borders,
			ui->tab2ComboBoxDosRotate->currentIndex(), symbols, ui->tab2ComboBoxLineSelector->currentIndex());
	else
		QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_NoNecessaryDataInFile);
	delete content;
}

void MainWindow::tab2BushButtonSetFontPressed()
{
	bool ok;
	QFontDialog fontDialog;
	const QRect windowLocation = geometry();
	fontDialog.setGeometry(windowLocation.x() + 100, windowLocation.y() + 50, 480, 360);
	const QFont font = fontDialog.getFont(&ok, tab2GraphFont);//QFontDialog::getFont(&ok, tab1GraphFont, this);
	if (ok) {
		tab2GraphFont = font;
	}
	else {

	}
}

void MainWindow::tab4QtAbout()
{
	QMessageBox::aboutQt(this);
}

void MainWindow::tab4LicenceMit()
{
	const QString text = STR_Licence;
	QMessageBox::information(this, STR_LicenseTitle, text);
}

void MainWindow::tab4Changelog()
{
	formChangelog->show();
}

void MainWindow::tab5QeDosLoad()
{
	QList<QString>* content = new QList<QString>();
	QString fileName = QFileDialog::getOpenFileName(this,
		STR_Dialog_OpenFile, settings->getLastPath(),
		"All Files (*)");
	if (fileName != "")
	{
		readFileFromFs(fileName, content);
		const QFileInfo fileinfo(fileName);
		settings->updatePath(fileinfo.absolutePath());
	}
	else
	{
		delete content;
		return;
	}
	qeDosData->parseDataNew(content);
}

void MainWindow::tab5UpdateParams(QString i)
{
	plotParams->updatePlotParams(5);
}

void MainWindow::tab5UpdateShowLine(int i)
{
	int selected = ui->tab5ComboBoxLineSelector->currentIndex();
	ui->tab5LoadFilecomboBox->setToolTip(ui->tab5LoadFilecomboBox->currentText());
	for (int i = 0; i < ui->tab5LoadFilecomboBox->currentIndex(); i++)
		selected += plotParams->tab5LinesCounter->at(i);
	plotParams->updatePlotParams(5);
	if (ui->tab5CheckBoxShow1->isChecked())
		ui->tab5ComboBoxLineSelector->setItemData(ui->tab5ComboBoxLineSelector->currentIndex(), QBrush(MenuSelectedGraph), Qt::ForegroundRole); //TextColorRole
	else
		ui->tab5ComboBoxLineSelector->setItemData(ui->tab5ComboBoxLineSelector->currentIndex(), QBrush(Qt::black), Qt::ForegroundRole);
}

void MainWindow::tab5ComboBoxLineSelectorIndexChanged(int selected)
{
	if (!plotParams->tab5LinesCounter->isEmpty())
	{
		for (int i = 0; i < ui->tab5LoadFilecomboBox->currentIndex(); i++)
			selected += plotParams->tab5LinesCounter->at(i);
	}

	if (selected != -1)
	{
		disconnect(ui->tab5SpinnerLineWidth, SIGNAL(valueChanged(QString)), this, SLOT(tab5UpdateParams(QString)));
		disconnect(ui->tab5ComboBoxLineType, SIGNAL(currentIndexChanged(QString)), this, SLOT(tab5UpdateParams(QString)));
		disconnect(ui->tab5CheckBoxShow1, SIGNAL(stateChanged(int)), this, SLOT(tab5UpdateShowLine(int)));
		disconnect(ui->tab5SpinnerLineMultiplier, SIGNAL(valueChanged(QString)), this, SLOT(tab5UpdateParams(QString)));
		ui->tab5SpinnerLineWidth->setValue(plotParams->tab5PlotParams->at(selected).width);
		ui->tab5SpinnerLineWidth->update();
		ui->ColorLable9->setPixmap(ColorIconDrawer::drawIcon(plotParams->tab5PlotParams->at(selected).color, this->window()->windowHandle()->devicePixelRatio()));
		ui->ColorLable10->update();
		ui->tab5CheckBoxShow1->setChecked(plotParams->tab5PlotParams->at(selected).show);
		ui->tab5CheckBoxShow1->update();
		ui->tab5ComboBoxLineType->setCurrentIndex(plotParams->tab5PlotParams->at(selected).styleId);
		ui->tab5ComboBoxLineType->update();
		ui->tab5SpinnerLineMultiplier->setValue(plotParams->tab5PlotParams->at(selected).multiplier);
		ui->tab5SpinnerLineMultiplier->update();
		connect(ui->tab5SpinnerLineWidth, SIGNAL(valueChanged(QString)), this, SLOT(tab5UpdateParams(QString)));
		connect(ui->tab5ComboBoxLineType, SIGNAL(currentIndexChanged(QString)), this, SLOT(tab5UpdateParams(QString)));
		connect(ui->tab5CheckBoxShow1, SIGNAL(stateChanged(int)), this, SLOT(tab5UpdateShowLine(int)));
		connect(ui->tab5SpinnerLineMultiplier, SIGNAL(valueChanged(QString)), this, SLOT(tab5UpdateParams(QString)));
	}
}

void MainWindow::tab5BushButtonSetFontPressed()
{
	bool ok;
	QFontDialog fontDialog;
	const QRect windowLocation = geometry();
	fontDialog.setGeometry(windowLocation.x() + 100, windowLocation.y() + 50, 480, 360);
	const QFont font = fontDialog.getFont(&ok, tab5GraphFont);//QFontDialog::getFont(&ok, tab1GraphFont, this);
	if (ok) {
		tab5GraphFont = font;
	}
	else {

	}
}

void MainWindow::tab5LoadFileDossPressed()
{
	const QStringList fileNames = QFileDialog::getOpenFileNames(this,
		STR_Dialog_OpenFile, settings->getLastPath(),
		tr("All Files (*)"));
	if (!fileNames.isEmpty())
	{
		int maxWidth = 0;
		disconnect(ui->tab5ComboBoxLineSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(tab5ComboBoxLineSelectorIndexChanged(int)));
		disconnect(ui->tab5LoadFilecomboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(tab5UpdateParamsFile(int)));
		int linesCount = 0;
		ui->tab5LoadFilecomboBox->clear();
		ui->tab5ComboBoxLineSelector->clear();
		plotParams->tab5LinesCounter->clear();
		int flagErrorDuringAdd = 0;
		for (auto fileName : fileNames)
		{
			QFont myFont("Arial", 9);
			QFontMetrics fm(myFont);
			int width = fm.width(fileName);
			if (width > maxWidth)
				maxWidth = width;
			QList<QString>* content = new QList<QString>();
			readFileFromFs(fileName, content);
			const QFileInfo fileinfo(fileName);
			settings->updatePath(fileinfo.absolutePath());
			int count = qeDosData->count(content);
			if (count>0)
			{
				try
				{
					qeDosData->parseDataNew(content);
				}
				catch(...)
				{
					count = 0;
				}
			}
			if (count>0)
			{
				ui->tab5LoadFilecomboBox->addItem(fileName);
				linesCount += count;
				plotParams->tab5LinesCounter->append(count);
			}
			else
			{
				flagErrorDuringAdd++;
			}
			QFileInfo file = QFileInfo(fileName);
			delete content;
		}
		if (flagErrorDuringAdd>0)
		{
			QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_SomeFilesNotContainedData.arg(flagErrorDuringAdd));
		}
		ui->tab5LoadFilecomboBox->view()->setMinimumWidth(maxWidth + maxWidth*0.05);
		connect(ui->tab5ComboBoxLineSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(tab5ComboBoxLineSelectorIndexChanged(int)));
		connect(ui->tab5LoadFilecomboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(tab5UpdateParamsFile(int)));
		plotParams->tab5SetCountOfLines(linesCount);
		if (ui->tab5LoadFilecomboBox->count()>0)
		{
			ui->tab5LoadFilecomboBox->setCurrentIndex(0);
			ui->tab5LoadFilecomboBox->setToolTip(ui->tab5LoadFilecomboBox->currentText());
			tab5UpdateParamsFile(0);
		}
		else
		{
			plotParams->tab5SetCountOfLines(1);
			ui->tab5ComboBoxLineSelector->addItem("1");
			ui->tab5ComboBoxLineSelector->setCurrentIndex(0);
		}
	}
}

void MainWindow::tab5DrawDosPressed()
{
	if (ui->tab5LoadFilecomboBox->count() > 0)
	{
	
		qeDosData->clear();
		try
		{
			for (int i = 0; i < ui->tab5LoadFilecomboBox->count(); i++)
			{
				QString filePath = ui->tab5LoadFilecomboBox->itemText(i);
				QList<QString>* content = new QList<QString>();
				if (filePath != "")
				{
					readFileFromFs(filePath, content);
					const QFileInfo fileinfo(filePath);
					settings->updatePath(fileinfo.absolutePath());
				}
				else
				{
					delete content;
					return;
				}
				qeDosData->parseAppend(content);
			}
		}
		catch(...)
		{
			QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_NoNecessaryDataInFile);
			return;
		}
		
		int selected = ui->tab5ComboBoxLineSelector->currentIndex();
		for (int i = 0; i < ui->tab5LoadFilecomboBox->currentIndex(); i++)
				selected += plotParams->tab5LinesCounter->at(i);
		plotParams->updatePlotParams(5);
		(new QeGraph(settings, "Plot", plotParams, tab5GraphFont, this))->draw(qeDosData, symbols, selected, ui->tab5ComboBoxDosRotate->currentIndex());
	}
	else
		QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_NoNecessaryDataInFile);
}

void MainWindow::tab5UpdateParamsFile(int selected)
{
	if (selected != -1)
	{
		ui->tab5LoadFilecomboBox->setToolTip(ui->tab5LoadFilecomboBox->currentText());
		int shift = 0;
		for (int i = 0; i < ui->tab5LoadFilecomboBox->currentIndex(); i++)
			shift += plotParams->tab5LinesCounter->at(i);
		disconnect(ui->tab5ComboBoxLineSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(tab5ComboBoxLineSelectorIndexChanged(int)));
		ui->tab5ComboBoxLineSelector->clear();
		for (int i = 0; i < plotParams->tab5LinesCounter->at(selected); i++)
		{
			ui->tab5ComboBoxLineSelector->addItem(QString::number(i + 1));
			if (plotParams->tab5PlotParams->at(shift+i).show)
				ui->tab5ComboBoxLineSelector->setItemData(i, QBrush(MenuSelectedGraph), Qt::ForegroundRole); //TextColorRole
			else
				ui->tab5ComboBoxLineSelector->setItemData(i, QBrush(Qt::black), Qt::ForegroundRole);
		}
		connect(ui->tab5ComboBoxLineSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(tab5ComboBoxLineSelectorIndexChanged(int)));
		ui->tab5ComboBoxLineSelector->setCurrentIndex(0);

		tab5ComboBoxLineSelectorIndexChanged(0);
	}
	else
		ui->tab5LoadFilecomboBox->setToolTip("");
}

void MainWindow::tab5LanguageChanged()
{
	if (settings->lang == "qt_en")
		settings->lang = "qt_ru";
	else
		settings->lang = "qt_en";

	settings->saveSettings();

	QMessageBox::warning(this, STR_LangTitle_ChangeWarning, STR_LangMessage_ChangeWarningRestartReq);
	qApp->quit();
	QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
}

void MainWindow::tab5LoadSurfConvButtonPressed()
{
	QList<QString>* content = new QList<QString>();
	const QString fileName = QFileDialog::getOpenFileName(this, STR_Dialog_OpenFile, settings->getLastPath(),
		"All Files (*)");
	if (fileName != "")
	{
		const QFileInfo fileinfo(fileName);
		settings->updatePath(fileinfo.absolutePath());
		readFileFromFs(fileName, content);
	}
	else
	{
		delete content;
		return;
	}

	qeSurfData->parseData(content);
	delete content;
	if (qeSurfData->oF.count() > 0)
	{
		qeSurfData->rotateData(ui->tab5SurfRotationSelector->currentIndex() * 90);
		QProgressDialog progressBar;
		progressBar.setValue(0);
		progressBar.setRange(0, 1);
		progressBar.show();

		QString path;
		QStringList pathTemp = fileName.split("/");
		
		QFileInfo fileInfo(fileName);
		path = fileInfo.path();
		const QDir dir(path);
		if (!dir.exists())
			dir.mkpath(".");
		const QString pathFull = path + "/" + fileInfo.baseName() + "-" + QString::number(
			ui->tab5SurfRotationSelector->currentIndex() * 90) + ".xlsx";
		QXlsx::Document xlsx;
		for (int j = 0; j < qeSurfData->oF.count(); j++)
		{
			xlsx.write(j + 1, 1, qeSurfData->oRepeatY[j]);
			xlsx.write(j + 1, 2, qeSurfData->oRepeatX[j]);
			xlsx.write(j + 1, 3, qeSurfData->oF[j]);
		}
		QApplication::processEvents();
		const bool success = xlsx.saveAs(pathFull); // save the document as 'Test.xlsx'
		if (success != true)
		{
			progressBar.close();
			QMessageBox::critical(this, STR_ErrorTitle_SaveError, STR_ErrorMessage_CantOpenFileForWrite.arg(pathFull));
			return;
		}
		progressBar.close();
		QMessageBox::information(this, STR_MessageBoxTitle_DataProcessed, STR_MessageBoxMessage_DataProcessedAndSaved);
	}
	else
		QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_NoNecessaryDataInFile);
}

void MainWindow::tab5PushButtonSetFontContourPressed()
{
	bool ok;
	QFontDialog fontDialog;
	const QRect windowLocation = geometry();
	fontDialog.setGeometry(windowLocation.x() + 100, windowLocation.y() + 50, 480, 360);
	const QFont font = fontDialog.getFont(&ok, tab5ContourGraphFont);
	if (ok) {
		tab5ContourGraphFont = font;
	}
	else {

	}
}

void MainWindow::tab5LoadQeBandButtonPressed()
{
	const QString fileName = QFileDialog::getOpenFileName(this,
		STR_Dialog_OpenFile, settings->getLastPath(),
		tr("Data files (*.dat *.freq);;All Files (*)"));
	if (fileName != "")
	{
		ui->tab5FileLine1->setText(fileName);
		ui->tab5FileLine1->setToolTip(fileName);
		const QFileInfo fileinfo(ui->tab5FileLine1->text());
		settings->updatePath(fileinfo.absolutePath());
	}
}

void MainWindow::tab5DrawZoneButtonPressed()
{
	QList<QString>* content = new QList<QString>();

	if (ui->tab5FileLine1->text() != "")
	{
		qeZoneData->clear();
		readFileFromFs(ui->tab5FileLine1->text(), content);
		qeZoneData->parseData(content);
		delete content;
		plotParams->updatePlotParams(5);
		if (qeZoneData->outputX.count() > 0)
			(new QeZoneGraph(settings, "Plot", plotParams, tab5GraphFont, this))->draw(qeZoneData,
				ui->tab5ZoneStructYMin->text().toDouble(), ui->tab5ZoneStructYMax->text().toDouble(), static_cast<QStandardItemModel*>(tab5tableView->model()), symbols);
		else
			QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_NoNecessaryDataInFile);
	}
	else
		QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_NoFileToDraw);
}

void MainWindow::screenChanged(QScreen* screen)
{
#ifdef OWN_HIGHDPI_SCALE
	resizeWidgets(screen->logicalDotsPerInch() / 96.0); 
	imageInit(ui, screen->logicalDotsPerInch() / 96.0);
	tableInit(ui, screen->logicalDotsPerInch() / 96.0);
	for (int i = 1; i < 11; i++)
	{
		setColotLabelById(i, screen->logicalDotsPerInch() / 96.0);
	}
	SetTab5TableCellSize(screen->logicalDotsPerInch() / 96.0);
	this->window()->windowHandle()->setScreen(screen);
#else
	this->window()->windowHandle()->setScreen(screen);
	imageInit(ui, this->window()->windowHandle()->devicePixelRatio());
	for (int i = 1; i < 11; i++)
	{
		setColotLabelById(i, this->window()->windowHandle()->devicePixelRatio());
	}
#endif
}

void MainWindow::tab5LoadQEDenButtonPressed()
{
	const QString fileName = QFileDialog::getOpenFileName(this,
		STR_Dialog_OpenFile, settings->getLastPath(),
		tr("Dat files (*.dat);;All Files (*)"));
	if (fileName != "")
	{
		ui->tab5FileLine3->setText(fileName);
		ui->tab5FileLine3->setToolTip(fileName);
		const QFileInfo fileinfo(ui->tab5FileLine3->text());
		settings->updatePath(fileinfo.absolutePath());
	}
}

void MainWindow::tab5PlotGraphicButtonPressed()
{
	QList<QString>* content = new QList<QString>();

	if (ui->tab5FileLine3->text() != "")
	{
		qeSurfData->clear();
		readFileFromFs(ui->tab5FileLine3->text(), content);
		qeSurfData->parseData(content);
		delete content;
		plotParams->updatePlotParams(5);
		if (qeSurfData->oF.count()>2)
			(new QEContourGraph(settings, "Plot", plotParams, tab5GraphFont, this))->draw(qeSurfData);
		else
			QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_NoNecessaryDataInFile);
	}
	else
		QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_NoFileToDraw);
}

void MainWindow::tab2PushButtonPdosLoadPressed()
{
	QList<QString>* content = new QList<QString>();
	QString fileName = QFileDialog::getOpenFileName(this,
		STR_Dialog_OpenFile, settings->getLastPath(),
		"Output file (*.out);;All Files (*)");
	if (fileName != "")
	{
		readFileFromFs(fileName, content);
		const QFileInfo fileinfo(fileName);
		settings->updatePath(fileinfo.absolutePath());
	}
	else
	{
		delete content;
		return;
	}

	const QVector<QVector<AtomTypes>> data = pdosParser->getAtomData(content);
	delete content;
	if (data.count() <= 0)
	{
		QMessageBox::warning(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_NoNecessaryDataInFile);
		return;
	}

	fileName = QFileDialog::getSaveFileName(nullptr,
		STR_Dialog_SaveFile, settings->getLastPath()+"PDOS.xlsx",
		tr("Excel file (*.xlsx);;All Files (*)"));
	if (fileName != "")
	{
		const QFileInfo fileinfo(fileName);
		settings->updatePath(fileinfo.absolutePath());
		bool success = filesSaver->saveHelpNumberOfFunctionsData(fileName, data);
		if (success != true)
		{
			QMessageBox::critical(this, STR_ErrorTitle_SaveError, STR_ErrorMessage_CantOpenFileForWrite.arg(fileName));
		}
		QMessageBox::information(this, STR_MessageBoxTitle_DataProcessed, STR_MessageBoxMessage_DataProcessedAndSaved);
	}
	
	ui->tab2PDOSNumbersTable->clear();
	ui->tab2PDOSNumbersTable->setRowCount(0);
	for (int i = 0; i < data.count(); i++)
	{
		for (int ii = 0; ii < data.at(i).count(); ii++)
		{
			ui->tab2PDOSNumbersTable->setRowCount(ui->tab2PDOSNumbersTable->rowCount() + 1);
			QTableWidgetItem* itm = new QTableWidgetItem(QString::number(data.at(i).at(ii).number));
			ui->tab2PDOSNumbersTable->setItem(ui->tab2PDOSNumbersTable->rowCount() - 1, 0, itm);
			itm = new QTableWidgetItem(data.at(i).at(ii).name);
			ui->tab2PDOSNumbersTable->setItem(ui->tab2PDOSNumbersTable->rowCount() - 1, 1, itm);
			itm = new QTableWidgetItem(data.at(i).at(ii).type);
			ui->tab2PDOSNumbersTable->setItem(ui->tab2PDOSNumbersTable->rowCount() - 1, 2, itm);
			itm = new QTableWidgetItem(QString::number(data.at(i).at(ii).end - data.at(i).at(ii).begin + 1));
			ui->tab2PDOSNumbersTable->setItem(ui->tab2PDOSNumbersTable->rowCount() - 1, 3, itm);
			itm = new QTableWidgetItem(QString::number(data.at(i).at(ii).begin));
			ui->tab2PDOSNumbersTable->setItem(ui->tab2PDOSNumbersTable->rowCount() - 1, 4, itm);
			itm = new QTableWidgetItem(QString::number(data.at(i).at(ii).end));
			ui->tab2PDOSNumbersTable->setItem(ui->tab2PDOSNumbersTable->rowCount() - 1, 5, itm);
		}
	}
	ui->tab2PDOSNumbersTable->setHorizontalHeaderLabels(QStringList() << STR_XLSX_AtomNumber << STR_XLSX_Atom << STR_XLSX_Type << STR_XLSX_FunctionNumber << STR_XLSX_StartNumber << STR_XLSX_EndNumber );
}
