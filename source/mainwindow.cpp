#include "mainwindow.h"


//Конструктор класса, инициализация необходимых классов,
//настройка интерфейса, восстановление предыдущх настроек
MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	settings = new SettingsKeeper(this);
	FileDialogsLoad* fileDiag = new FileDialogsLoad(ui, this, settings);
	graphicsData = new GraphicsData();
	bandData = new BandData();
	surfData = new SurfData();
	CTConvertor = new CrystalTopondConvertors();
	filesSaver = new FilesSaver();
	plotParams = new PlotParameters(ui, this);
	iconDrawer = new ColorIconDrawer();
	pdosParser = new PdosParser();
	symbols = new MathSymbols(this);
	atomsConvert = new AtomConversion(ui, settings);
	GraphsA = new QVector<BasicGraphBuild*>();
	GraphsB = new QVector<DOSGraphBuilder*>();
	GraphsC = new QVector<ZoneStructGraphBuilder*>();

	ui->setupUi(this);
	setupUiFields(ui);
	setUiButtonsGroups(ui);
	setUiColorLabels(ui);
	tab1GraphFont.setFamily("Times New Roman");
	tab1GraphFont.setPointSize(18);
	tab2GraphFont.setFamily("Times New Roman");
	tab2GraphFont.setPointSize(18);

	tmr = new QTimer(this); 
	tmr->setInterval(5000); 
	connect(tmr, SIGNAL(timeout()), this, SLOT(garbageCollector())); 
	tmr->start();

	
	
    connect(ui->tab3AtomsConvertButton,     SIGNAL(clicked()),                  this,       SLOT(atomsConvertButtonPressed()));
    connect(ui->tab3AtomsSearchButton,      SIGNAL(clicked()),                  this,       SLOT(atomsSearchButtonPressed()));
    connect(ui->tab3LoadFileConvertXfX,     SIGNAL(clicked()),                  this,       SLOT(LoadFileConvertXfXButtonPressed()));
    connect(ui->tab3LoadFilesConvertDOS,    SIGNAL(clicked()),                  this,       SLOT(tab3LoadFilesConvertDOSButtonPressed()));
    connect(ui->tab3SurfF25Button,          SIGNAL(clicked()),                  this,       SLOT(tab3SurfF25ButtonPressed()));
    connect(ui->tab3SurfConvertButton,      SIGNAL(clicked()),                  this,       SLOT(tab3SurfConvertButtonPressed()));
    connect(ui->tab3ButtonCrystalToTopond,  SIGNAL(clicked()),                  this,       SLOT(tab3ButtonCrystalToTopondPressed()));
    connect(ui->tab3ButtonTopondToCrystal,  SIGNAL(clicked()),                  this,       SLOT(tab3ButtonTopondToCrystalPressed()));
    connect(ui->tab2buttonDrawZoneStruct,   SIGNAL(clicked()),                  this,       SLOT(tab2buttonDrawZoneStructPressed()));
    connect(ui->ColorButtonGroup,           SIGNAL(buttonClicked(int)),         this,       SLOT(ColorChangeButtonClicked(int)));
    connect(ui->DeleteButtonGroup,          SIGNAL(buttonClicked(int)),         this,       SLOT(DeleteFileStringButtonClicked(int)));
    connect(ui->HelpButtonGroup,            SIGNAL(buttonClicked(int)),         this,       SLOT(HelpButtonClicked(int)));
    connect(ui->LoadFileButtonGroup,        SIGNAL(buttonClicked(int)),         fileDiag,   SLOT(LoadFileButtonCliked(int)));
    connect(ui->tab1LoadFilesTjMolP2,       SIGNAL(clicked()),                  fileDiag,   SLOT(FileDialogMolTrajP2Load()));
    connect(ui->tab1PlotGraphic,            SIGNAL(clicked()),                  this,       SLOT(plotButtonTab1Clicked()));
    connect(ui->tab1FontChangeButton,       SIGNAL(clicked()),                  this,       SLOT(fontChangeButtonPressed()));
    connect(ui->tab2SpinnerLineWidth,       SIGNAL(valueChanged(QString)),      this,       SLOT(tab2UpdateParams(QString)));
    connect(ui->tab2ComboBoxLineType,       SIGNAL(currentIndexChanged(QString)),this,      SLOT(tab2UpdateParams(QString)));
    connect(ui->tab2CheckBoxShow1,          SIGNAL(stateChanged(int)),          this,       SLOT(tab2UpdateShowLine(int)));
    connect(ui->tab2SpinnerLineMultiplier,  SIGNAL(valueChanged(QString)),      this,       SLOT(tab2UpdateParams(QString)));
    connect(ui->tab2ComboBoxLineSelector,   SIGNAL(currentIndexChanged(int)),   this,       SLOT(tab2ComboBoxLineSelectorIndexChanged(int)));
    connect(ui->tab2ButtonDrawDOS,          SIGNAL(clicked()),                  this,       SLOT(tab2ButtonDrawDOSPressed()));
    connect(ui->tab2BushButtonSetFont,      SIGNAL(clicked()),                  this,       SLOT(tab2BushButtonSetFontPressed()));
    connect(ui->tab4QtAbout,                SIGNAL(clicked()),                  this,       SLOT(tab4QtAbout()));
    connect(ui->tab2LoadFilef25DOSS,        SIGNAL(clicked()),                  this,       SLOT(tab2LoadFilef25DOSSPressed()));
    connect(ui->tab4LicenceMIT,             SIGNAL(clicked()),                  this,       SLOT(tab4LicenceMIT()));
    connect(ui->tab2PushButtonPDOSLoad,     SIGNAL(clicked()),                  this,       SLOT(tab2PushButtonPDOSLoadPressed()));	
    //connect(ui->menuPictureSetup,			 SIGNAL(triggered()),				   this,       SLOT(showPictureSettings()));

	//Корректировочный коэффициент масштабирования
	//графиков на дисплеях с масштабом !=100%
	QScreen* srn = QApplication::screens().at(0);
	auto b= srn->availableSize();
	auto height = b.height()*0.90;
	if (height > 600) height = 600;
	plotParams->drawRes = height;
	plotParams->drawQuality = settings->quality;
	plotParams->drawScale = settings->scale;
	plotParams->preferFormat = settings->imageType;
}

MainWindow::~MainWindow()
{
	settings->SaveSettings();
	delete ui;
}

void MainWindow::showPictureSettings()
{
    if (form!=nullptr)
    {
        form->close();
        delete form;
    }
    form = new PictureSettings(plotParams, settings,this);
	form->show();
}

void MainWindow::garbageCollector()
{
	for (int i = 0; i < GraphsC->size(); i++)
	{
		if (GraphsC->at(i)->isClosed())
		{
			delete GraphsC->at(i);
			GraphsC->removeAt(i);
			i = 0;
		}
	}
}

void MainWindow::colorChangeButtonClicked(int id) const
{
	QColorDialog colorPickerMenu;
	const QRect windowLocation = geometry();
	colorPickerMenu.setGeometry(windowLocation.x() + 100, windowLocation.y() + 50, 522, 393);
	colorPickerMenu.exec();
	const QColor choosenColor = colorPickerMenu.selectedColor();
	if (!choosenColor.isValid()) return;
	const QPixmap colorIcon = iconDrawer->draw_icon(choosenColor);
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

void MainWindow::deleteFileStringButtonClicked(int id) const
{
	QString lineName;
	if (id < 7)
		lineName = QString("tab1FileLine%1").arg(id);
	else
		lineName = QString("tab2FileLine%1").arg(id - 6);
	QLineEdit* lineEdit = findChild<QLineEdit*>(lineName);
	if (lineEdit != nullptr)
	{
		lineEdit->clear();
		if (id == 8)
		{
			ui->tab2ComboBoxLineSelector->clear();
			plotParams->setCountOfLines(1);
			ui->tab2ComboBoxLineSelector->addItem("1");
			ui->tab2ComboBoxLineSelector->setCurrentIndex(0);
		}
	}
}

void MainWindow::helpButtonClicked(int id)
{
	const QRect windowLocation = geometry();
	if (id == 2)
	{
		HelpMatrixWidget* a = new HelpMatrixWidget(ui, windowLocation);
		a->installEventFilter(a);
	}
	else
	{
		const QString helpFile = QString(":resource/help/HELP%1.png").arg(id);
		const QPixmap helpPixmap = QPixmap(helpFile);
		HelpWindow(helpPixmap, windowLocation, this);
	}
}

void MainWindow::plotButtonTab1Clicked()
{
	//Проверки на безопастность и наличие файлов
	if (ui->tab1FileLine1->text()+ ui->tab1FileLine2->text()+ ui->tab1FileLine3->text()+ ui->tab1FileLine4->text()+ ui->tab1FileLine5->text()+ ui->tab1FileLine6->text() == "")
	{
        QMessageBox::warning(this, tr("Ошибка парсинга"), tr("Не указан ни один файл для построения!"));
		return;
	}

	if (ui->tab1FileLine1->text() + ui->tab1FileLine2->text() + ui->tab1FileLine3->text() + ui->tab1FileLine4->text() + ui->tab1FileLine6->text() == "" && ui->tab1FileLine5->text()!="")
	{
        QMessageBox::warning(this, tr("Ошибка парсинга"), tr("Не указаны файлы с данными для построения!"));
		return;
	}

	if (ui->tab1FileLine1->text() + ui->tab1FileLine2->text() + ui->tab1FileLine3->text() != "" &&
		ui->tab1FileLine5->text() =="" && ui->tab1FileLine4->text() + ui->tab1FileLine6->text() != "")
	{
        QMessageBox::warning(this, tr("Ошибка парсинга"), tr("Не указан файл *.outp, Molgrath/Trajgrad/P2dcrynp не будут построены!"));
	}

	//Сохранение путей до файлов в единый массив для передачи в парсер
	QList<QString> fields;
	fields.append(ui->tab1FileLine1->text());
	fields.append(ui->tab1FileLine2->text());
	fields.append(ui->tab1FileLine3->text());
	fields.append(ui->tab1FileLine5->text());
	plotParams->updatePlotParams(1);
	QList<QString>* content = new QList<QString>();

	int success = graphicsData->GetAndParseMainData(fields, ui->tab1AtomsCutOff->text().toDouble());
	if (success != 1)
	{
		switch (success)
		{
		case 0:
            QMessageBox::warning(this, tr("Ошибка парсинга"), tr("В файле .outp отсутствуют необходимые данные или файл поврежден!"));
			break;
		case -1:
            QMessageBox::warning(this, tr("Ошибка парсинга"), tr("В файле Trajgrad.dat отсутствуют необходимые данные или файл поврежден!"));
			break;
		case -2:
            QMessageBox::warning(this, tr("Ошибка парсинга"), tr("В файле Molgrapf.dat отсутствуют необходимые данные или файл поврежден!"));
			break;
		case -3:
            QMessageBox::warning(this, tr("Ошибка парсинга"), tr("В файле P2dcrynp.dat отсутствуют необходимые данные или файл поврежден!"));
			break;
		default:
			break;
		}


		graphicsData->clear();
        delete(content);
		return;
	}
	
	if(fields[0]+ fields[1]+ fields[2]!="" && fields[3]=="" && ui->tab1FileLine6->text() == "" && ui->tab1FileLine4->text() == "")
	{
        QMessageBox::warning(this, tr("Ошибка парсинга"), tr("Не указан файл *.outp!"));
        delete content;
		return;
	}

	
	if (ui->tab1FileLine6->text() != "")
	{
		read_file_from_fs(ui->tab1FileLine6->text(), content);
		bandData->ParseData(content, ui->tab1uhf->isChecked());
	}
	else
		bandData->clear();

	if (ui->tab1FileLine4->text() != "")
	{
		read_file_from_fs(ui->tab1FileLine4->text(), content);
		surfData->ParseData(content);
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
					new BasicGraphBuild(plotParams, tab1GraphFont, ui->tab1ShowAxis->isChecked(), i, ui->tab1uhf->isChecked(),
						settings, graphicsData, surfData, bandData, ui->tab1ComboBoxRotate->currentIndex()*90, this);
				}

			}
			else
				new BasicGraphBuild(plotParams, tab1GraphFont, ui->tab1ShowAxis->isChecked(), 0,
					ui->tab1uhf->isChecked(), settings, graphicsData, surfData, bandData, ui->tab1ComboBoxRotate->currentIndex() * 90, this);
		}
		else
			new BasicGraphBuild(plotParams, tab1GraphFont, ui->tab1ShowAxis->isChecked(), 0, ui->tab1uhf->isChecked(),
				settings, graphicsData, surfData, bandData, ui->tab1ComboBoxRotate->currentIndex() * 90, this);
	}

}

void MainWindow::fontChangeButtonPressed() {
	bool ok;
	QFontDialog test;
	const auto window_location = geometry();
	test.setGeometry(window_location.x() + 100, window_location.y() + 50, 480, 360);
	QFont font = QFontDialog::getFont(&ok, tab1GraphFont);//QFontDialog::getFont(&ok, tab1GraphFont, this);
	if (ok) {
		tab1GraphFont = font;
		ui->tab1FontSize->setValue(font.pointSize());
	}
	else {

	}
}

void MainWindow::atomsConvertButtonPressed()
{
	atomsConvert->convertAtoms();
}

void MainWindow::atomsSearchButtonPressed()
{
	atomsConvert->convertAndSearchAtoms();
}

void MainWindow::LoadFileConvertXfXButtonPressed()
{
	QList<QString>* content = new QList<QString>();
	QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open file"), settings->GetLastPath(),
		"*.f25 (*.f25);;All Files (*)");
	if (fileName != "")
	{
		QFileInfo fileinfo(fileName);
		settings->UpdatePath(fileinfo.absolutePath());
		read_file_from_fs(fileName, content);
	}
	else
    {
        delete content;
		return;
    }

	bandData->ParseData(content, ui->tab3uhfZoneStruct);
	delete content;
	if (bandData->outputBAND.count() > 0)
	{
		bool success = filesSaver->saveBANDData(fileName, bandData, ui->tab3ZoneStructYMin->text().toDouble(), ui->tab3ZoneStructYMax->text().toDouble(), ui->tab3uhfZoneStruct->isChecked());
		if (success == false)
		{
            QMessageBox::critical(this, tr("Ошибка сохранения"), tr("'") + filesSaver->errorData.ErrorFile + tr("' не удается открыть для записи!"));
			return;
		}
        QMessageBox::information(this, tr("Данные обработаны"), tr("Данные обработаны и сохранены!"));
	}
	else
        QMessageBox::warning(this, tr("Ошибка парсинга"), tr("В предоставленном файле отсутствуют необходимые данные или файл поврежден!"));
}

void MainWindow::tab3LoadFilesConvertDOSButtonPressed()
{
	QList<QString>* content = new QList<QString>();
	QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open file"), settings->GetLastPath(),
		"*.f25 (*.f25);;All Files (*)");
	if (fileName != "")
	{
		QFileInfo fileinfo(fileName);
		settings->UpdatePath(fileinfo.absolutePath());
		read_file_from_fs(fileName, content);
	}
	else
    {
        delete content;
		return;
    }

	bandData->ParseData(content);
	delete content;
	if (bandData->outputCOHP.count() > 0 || bandData->outputCOOP.count() > 0 || bandData->outputDOSS.count() > 0)
	{
		bool success = filesSaver->SaveDosData(fileName, bandData);
		if (success == false)
		{
            QMessageBox::critical(this, tr("Ошибка сохранения"), tr("'") + filesSaver->errorData.ErrorFile + tr("' не удается открыть для записи!"));
			return;
		}
        QMessageBox::information(this, tr("Данные обработаны"), tr("Данные обработаны и сохранены!"));
	}
	else
        QMessageBox::warning(this, tr("Ошибка парсинга"), tr("В предоставленном файле отсутствуют необходимые данные или файл поврежден!"));
}

void MainWindow::tab3SurfF25ButtonPressed()
{
	QList<QString>* content = new QList<QString>();
	QString file_name = QFileDialog::getOpenFileName(this,
        tr("Open file"), settings->GetLastPath(),
		"*.f25 (*.f25);;All Files (*)");
	if (file_name != "")
	{
		QFileInfo file_info(file_name);
		settings->UpdatePath(file_info.absolutePath());
		read_file_from_fs(file_name, content);
	}
	else
    {
        delete content;
		return;
    }

	bandData->ParseData(content, ui->tab3uhff25->isChecked());
	delete content;
	if (bandData->outputMAPN.count() > 0)
	{
		bool success = filesSaver->saveMAPNData(file_name, bandData, ui->tab3SurfRotationSelector->currentIndex() * 90);
		if (success == false)
		{
            QMessageBox::critical(this, tr("Ошибка сохранения"), tr("'") + filesSaver->errorData.ErrorFile + tr("' не удается открыть для записи!"));
			return;
		}
        QMessageBox::information(this, tr("Данные обработаны"), tr("Данные обработаны и сохранены!"));
	}
	else
        QMessageBox::warning(this, tr("Ошибка парсинга"), tr("В предоставленном файле отсутствуют необходимые данные или файл поврежден!"));
}

void MainWindow::tab3SurfConvertButtonPressed()
{
	QList<QString>* content = new QList<QString>();
	QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open file"), settings->GetLastPath(),
		"*.dat (*.dat);;All Files (*)");
	if (fileName != "")
	{
		QFileInfo fileinfo(fileName);
		settings->UpdatePath(fileinfo.absolutePath());
		read_file_from_fs(fileName, content);
	}
	else
    {
		delete content;
		return;
    }

	surfData->ParseData(content);
	delete content;
	if (surfData->oF.count() > 0)
	{
		surfData->RotateData(ui->tab3SurfRotationSelector->currentIndex() * 90);
		QProgressDialog progressBar;
		progressBar.setValue(0);
		progressBar.setRange(0, 1);
		progressBar.show();

		QString path;
		QStringList pathTemp = fileName.split("/");


		for (int i = 0; i < pathTemp.count() - 1; i++)
			path += pathTemp.at(i) + "/";
		path += "TOPOND";
		QDir dir(path);
		if (!dir.exists())
			dir.mkpath(".");
		QString pathFull = path + "/" + pathTemp[pathTemp.count() - 1].mid(4, 4) + "-" + QString::number(
			ui->tab3SurfRotationSelector->currentIndex() * 90) + ".xlsx";
		QXlsx::Document xlsx;
		for (int j = 0; j < surfData->oF.count(); j++)
		{
			xlsx.write(j + 1, 1, surfData->oRepeatY[j]);
			xlsx.write(j + 1, 2, surfData->oRepeatX[j]);
			xlsx.write(j + 1, 3, surfData->oF[j]);
		}
		QApplication::processEvents();
		bool success = xlsx.saveAs(pathFull); // save the document as 'Test.xlsx'
		if (success != true)
		{
			progressBar.close();
            QMessageBox::critical(this, tr("Ошибка сохранения"), tr("'") + pathFull + tr("' не удается открыть для записи!"));
			return;
		}
		progressBar.close();
        QMessageBox::information(this, tr("Данные обработаны"), tr("Данные обработаны и сохранены!"));
	}
	else
        QMessageBox::warning(this, tr("Ошибка парсинга"), tr("В предоставленном файле отсутствуют необходимые данные или файл поврежден!"));
}

void MainWindow::tab3ButtonCrystalToTopondPressed()
{
	QList<QString>* content = new QList<QString>();
	QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open file"), settings->GetLastPath(),
		"Output file (*.outp);;All Files (*)");
	if (fileName != "")
	{
		QFileInfo fileinfo(fileName);
		settings->UpdatePath(fileinfo.absolutePath());
		read_file_from_fs(fileName, content);
	}
	else
    {
        delete content;
		return;
    }

	CTConvertor->ConvertCrystalToTopond(content);

	delete content;

	if (CTConvertor->output != "")
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
			// We're going to streaming text to the file
			QTextStream stream(&file);
			stream << CTConvertor->output;
			file.close();
		}
		else
		{
            QMessageBox::critical(this, tr("Ошибка сохранения"), tr("'") + path + tr("' не удается открыть для записи!"));
			return;
		}
        QMessageBox::information(this, tr("Данные обработаны"), tr("Данные обработаны и сохранены!"));
	}
	else
        QMessageBox::warning(this, tr("Ошибка парсинга"), tr("В предоставленном файле отсутствуют необходимые данные или файл поврежден!"));
}

void MainWindow::tab3ButtonTopondToCrystalPressed()
{
	QList<QString>* content = new QList<QString>();
	QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open file"), settings->GetLastPath(),
		"Output file (*.outp);;All Files (*)");
	if (fileName != "")
	{
		QFileInfo fileinfo(fileName);
		settings->UpdatePath(fileinfo.absolutePath());
		read_file_from_fs(fileName, content);
	}
	else
    {
        delete content;
		return;
    }
	CTConvertor->ConvertTopondToCrystal(content);

	delete content;

	if (CTConvertor->output != "")
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
			stream << CTConvertor->output;
			file.close();
		}
		else
		{
            QMessageBox::critical(this, tr("Ошибка сохранения"), tr("'") + path + tr("' не удается открыть для записи!"));
			return;
		}
        QMessageBox::information(this, tr("Данные обработаны"), tr("Данные обработаны и сохранены!"));
	}
	else
        QMessageBox::warning(this, tr("Ошибка парсинга"), tr("В предоставленном файле отсутствуют необходимые данные или файл поврежден!"));
}

void MainWindow::tab2buttonDrawZoneStructPressed()
{
	QList<QString>* content = new QList<QString>();
	if (ui->tab2FileLine1->text() != "")
	{
		{
			QFileInfo fileinfo(ui->tab2FileLine1->text());
			settings->UpdatePath(fileinfo.absolutePath());
			read_file_from_fs(ui->tab2FileLine1->text(), content);
		}
	}
	else
	{
        delete content;
        QMessageBox::warning(this, tr("Ошибка загрузки"), tr("Не указан файл построения!"));
		return;
	}
	bandData->ParseData(content);

	delete content;

	plotParams->updatePlotParams(2);
	ui->tab2ComboBoxLineSelector->setCurrentIndex(0);
	ui->tab2ComboBoxLineSelector->update();
	if (bandData->outputBAND.count() > 0)
	{
		double numbersToBuild[2];

		if (plotParams->uhf)
		{
			for (int i = 0; i < 2; i++)
			{
				numbersToBuild[0] = bandData->oXBand[bandData->oXBand.size() / 2 * i];
				numbersToBuild[1] = bandData->oXBand[(bandData->oXBand.size() / 2) * (i + 1) - 1];
				GraphsC->append(new ZoneStructGraphBuilder(bandData, ui->tab2ZoneStructYMin->text().toDouble(),
					ui->tab2ZoneStructYMax->text().toDouble(), ui->tab2LineKPoints->text(),
                    plotParams, tab2GraphFont, numbersToBuild, QString(("Зонная структура " + std::to_string(i + 1)).c_str()), settings, symbols, this));
			}
		}
		else
		{
			numbersToBuild[0] = 0;
			numbersToBuild[1] = bandData->oXBand[bandData->oXBand.size() - 1];
			GraphsC->append(new ZoneStructGraphBuilder(bandData, ui->tab2ZoneStructYMin->text().toDouble(),
				ui->tab2ZoneStructYMax->text().toDouble(), ui->tab2LineKPoints->text(),
                plotParams, tab2GraphFont, numbersToBuild, tr("Зонная структура"), settings, symbols, this));
		}

	}

	else
        QMessageBox::warning(this, tr("Ошибка парсинга"), tr("В предоставленном файле отсутсвуют необходимые данные или файл поврежден!"));
}

void MainWindow::tab2UpdateParams(QString i)
{
	plotParams->updatePlotParams(2);
}

void MainWindow::tab2UpdateShowLine(int i)
{
	plotParams->updatePlotParams(2);
	if (ui->tab2CheckBoxShow1->isChecked())
		ui->tab2ComboBoxLineSelector->setItemData(ui->tab2ComboBoxLineSelector->currentIndex(), QBrush(Qt::red), Qt::ForegroundRole); //TextColorRole
	else
		ui->tab2ComboBoxLineSelector->setItemData(ui->tab2ComboBoxLineSelector->currentIndex(), QBrush(Qt::black), Qt::ForegroundRole);
}

void MainWindow::tab2LoadFilef25DOSSPressed()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		tr("Open file"), settings->GetLastPath(),
		tr("f25 files (*.f25);;All Files (*)"));
	if (fileName != "")
	{
		QList<QString>* content = new QList<QString>();
		read_file_from_fs(fileName, content);
		QFileInfo fileinfo(fileName);
		settings->UpdatePath(fileinfo.absolutePath());
		ui->tab2FileLine2->setText(fileName);
		QVector<int> count = bandData->CountData(content);
		if (count[0] > 0 || count[1] > 0 || count[2] > 0)
		{
			int sum = count[0] + count[1] + count[2];
			ui->tab2ComboBoxLineSelector->clear();
			plotParams->setCountOfLines(sum);
			for (int i = 0; i < count[0]; i++)
				ui->tab2ComboBoxLineSelector->addItem(QString::number(i + 1) + ": COHP");
			for (int i = 0; i < count[1]; i++)
				ui->tab2ComboBoxLineSelector->addItem(QString::number(i + 1) + ": COOP");
			for (int i = 0; i < count[2]; i++)
				ui->tab2ComboBoxLineSelector->addItem(QString::number(i + 1) + ": DOS");
			ui->tab2ComboBoxLineSelector->setCurrentIndex(0);
		}
		else
		{
			ui->tab2ComboBoxLineSelector->clear();
			plotParams->setCountOfLines(1);
			ui->tab2ComboBoxLineSelector->addItem("1");
			ui->tab2ComboBoxLineSelector->setCurrentIndex(0);
		}
		delete content;
	}
}

void MainWindow::tab2ComboBoxLineSelectorIndexChanged(int selected)
{
	if (selected != -1)
	{
		disconnect(ui->tab2SpinnerLineWidth, SIGNAL(valueChanged(QString)), this, SLOT(tab2UpdateParams(QString)));
		disconnect(ui->tab2ComboBoxLineType, SIGNAL(currentIndexChanged(QString)), this, SLOT(tab2UpdateParams(QString)));
		disconnect(ui->tab2CheckBoxShow1, SIGNAL(stateChanged(int)), this, SLOT(tab2UpdateShowLine(int)));
		disconnect(ui->tab2SpinnerLineMultiplier, SIGNAL(valueChanged(QString)), this, SLOT(tab2UpdateParams(QString)));
		ui->tab2SpinnerLineWidth->setValue(plotParams->tab2PlotParams->at(selected).width);
		ui->tab2SpinnerLineWidth->update();
		ui->ColorLable8->setPixmap(iconDrawer->draw_icon(plotParams->tab2PlotParams->at(selected).color));
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

void MainWindow::tab2ButtonDrawDOSPressed()
{
	QList<QString>* content = new QList<QString>();
	if (ui->tab2FileLine2->text() != "")
	{
		read_file_from_fs(ui->tab2FileLine2->text(), content);
		QFileInfo fileinfo(ui->tab2FileLine2->text());
		settings->UpdatePath(fileinfo.absolutePath());
	}
	else
	{
        delete content;
        QMessageBox::warning(this, tr("Ошибка загрузки"), tr("Не указан файл построения!"));
		return;
	}

	bandData->ParseData(content);
	plotParams->updatePlotParams(2);
	double borders[4] = { ui->tab2DOSXMin->text().toDouble(),ui->tab2DOSXMax->text().toDouble(),ui->tab2DOSYMin->text().toDouble(),ui->tab2DOSYMax->text().toDouble() };
	if (bandData->outputCOHP.count() > 0 || bandData->outputDOSS.count() > 0 || bandData->outputCOOP.count() > 0)
		new DOSGraphBuilder(bandData, borders, plotParams, tab2GraphFont, ui->tab2ComboBoxDosRotate->currentIndex(), settings, symbols,ui->tab2ComboBoxLineSelector->currentIndex(), this);
	else
        QMessageBox::warning(this, tr("Ошибка парсинга"), tr("В предоставленном файле отсутсвуют необходимые данные или файл поврежден!"));
	delete content;
}

void MainWindow::tab2BushButtonSetFontPressed()
{
	bool ok;
	QFontDialog test;
	QRect windowLocation = geometry();
	test.setGeometry(windowLocation.x() + 100, windowLocation.y() + 50, 480, 360);
	QFont font = test.getFont(&ok, tab2GraphFont);//QFontDialog::getFont(&ok, tab1GraphFont, this);
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

void MainWindow::tab4LicenceMIT()
{
    QString text = tr("Лицензия MIT\n\nCopyright © 2020 КемГУ\n\nДанная лицензия разрешает лицам, получившим копию данного программного"
		" обеспечения и сопутствующей документации (в дальнейшем именуемыми «Программное Обеспечение»), безвозмездно"
		" использовать Программное Обеспечение без ограничений, включая неограниченное право на использование, копирование,"
		" изменение, слияние, публикацию, распространение, сублицензирование и/или продажу копий Программного Обеспечения, "
		"а также лицам, которым предоставляется данное Программное Обеспечение, при соблюдении следующих условий:\n\n"
		"Указанное выше уведомление об авторском праве и данные условия должны быть включены во все копии или значимые "
		"части данного Программного Обеспечения.\n\nДАННОЕ ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ ПРЕДОСТАВЛЯЕТСЯ «КАК ЕСТЬ», БЕЗ КАКИХ-ЛИБО"
		" ГАРАНТИЙ, ЯВНО ВЫРАЖЕННЫХ ИЛИ ПОДРАЗУМЕВАЕМЫХ, ВКЛЮЧАЯ ГАРАНТИИ ТОВАРНОЙ ПРИГОДНОСТИ, СООТВЕТСТВИЯ ПО ЕГО КОНКРЕТНОМУ "
		"НАЗНАЧЕНИЮ И ОТСУТСТВИЯ НАРУШЕНИЙ, НО НЕ ОГРАНИЧИВАЯСЬ ИМИ. НИ В КАКОМ СЛУЧАЕ АВТОРЫ ИЛИ ПРАВООБЛАДАТЕЛИ НЕ НЕСУТ "
        "ОТВЕТСТВЕННОСТИ ПО КАКИМ-ЛИБО ИСКАМ, ЗА УЩЕРБ ИЛИ ПО ИНЫМ ТРЕБОВАНИЯМ, В ТОМ ЧИСЛЕ, ПРИ ДЕЙСТВИИ КОНТРАКТА, ДЕЛИКТЕ "
        "ИЛИ ИНОЙ СИТУАЦИИ, ВОЗНИКШИМ ИЗ-ЗА ИСПОЛЬЗОВАНИЯ ПРОГРАММНОГО ОБЕСПЕЧЕНИЯ ИЛИ ИНЫХ ДЕЙСТВИЙ С ПРОГРАММНЫМ ОБЕСПЕЧЕНИЕМ.");
    QMessageBox::information(this, tr("Лицензионное соглашение"), text);
}

void MainWindow::tab2PushButtonPDOSLoadPressed()
{
	QList<QString>* content = new QList<QString>();
	QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open file"), settings->GetLastPath(),
		"Output file (*.out);;All Files (*)");
	if (fileName != "")
	{
		read_file_from_fs(fileName, content);
		QFileInfo fileinfo(fileName);
		settings->UpdatePath(fileinfo.absolutePath());
	}
	else
    {
        delete content;
		return;
    }

	QVector<QVector<AtomTypes>> data = pdosParser->getAtomData(content);
	delete content;
	if (data.count() <= 0)
	{
        QMessageBox::warning(this, tr("Ошибка парсинга"), tr("В предоставленном файле отсутсвуют необходимые данные или файл поврежден!"));
		return;
	}

	fileName = QFileDialog::getSaveFileName(nullptr,
        tr("Сохранить данные"), settings->GetLastPath()+"PDOS.xlsx",
        tr("Excel file (*.xlsx);;All Files (*)"));
	if (fileName != "")
	{
		QFileInfo fileinfo(fileName);
		settings->UpdatePath(fileinfo.absolutePath());
		QXlsx::Document xlsx;
        xlsx.write(1, 1, tr("№ атома"));
        xlsx.write(1, 2, tr("Атом"));
        xlsx.write(1, 3, tr("Тип"));
        xlsx.write(1, 4, tr("Число ф-й"));
        xlsx.write(1, 5, tr("Номера баз. ф-й"));
		int counter = 2;
		for (int i = 0; i < data.count(); i++)
		{
			for (int ii = 0; ii < data.at(i).count(); ii++)
			{
				xlsx.write(counter, 1, QString::number(data.at(i).at(ii).number));
				xlsx.write(counter, 2, data.at(i).at(ii).name);
				xlsx.write(counter, 3, data.at(i).at(ii).type);
				xlsx.write(counter, 4, QString::number(data.at(i).at(ii).end - data.at(i).at(ii).begin + 1));
				QString temp;
				for (int j = data.at(i).at(ii).begin; j <= data.at(i).at(ii).end; j++)
					temp += QString::number(j) + " ";
				xlsx.write(counter, 5, temp);
				counter++;
			}
		}
		xlsx.setColumnWidth(1, 10);
		xlsx.setColumnWidth(2, 10);
		xlsx.setColumnWidth(3, 10);
		xlsx.setColumnWidth(4, 15);
		xlsx.setColumnWidth(5, 50);
		QApplication::processEvents();
		bool success = xlsx.saveAs(fileName); // save the document as 'Test.xlsx'
		if (success != true)
		{
            QMessageBox::critical(this, tr("Ошибка сохранения"), tr("'") + fileName + tr("' не удается открыть для записи!"));
		}
        QMessageBox::information(this, tr("Данные обработаны"), tr("Данные обработаны и сохранены!"));
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
    ui->tab2PDOSNumbersTable->setHorizontalHeaderLabels(QStringList() << tr("№ атома") << tr("Атом") << tr("Тип") << tr("Число ф-й") << tr("N нач.") << tr("N кон."));
}
