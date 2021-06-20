#include "zonestructgraphbuilder.h"

ZoneStructGraphBuilder::ZoneStructGraphBuilder(BandData* graphics, double min, double max, QString kPoints,
	PlotParameters* params, QFont font, double buildNumbers[2], QString title, SettingsKeeper* settings, MathSymbols *symbols, QWidget* parent) : QWidget(parent)
{
	
	customPlot = new QCustomPlot();
	//customPlot->setOpenGl(true,16);
	QPen pen;
	this->plotParams = params;
	this->parent = parent;
	this->settings = settings;
	
	pen.setStyle(params->tab2PlotParams->at(0).style);
	pen.setColor(params->tab2PlotParams->at(0).color);
	pen.setWidthF(params->tab2PlotParams->at(0).width);
	QCPCurve* newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);

	for (int i = 0; i < graphics->outputBAND.count(); i++)
	{

		QVector<double> tempCorrectionY;
		QVector<double> tempCorrectionX;
		for (int j = 0; j < graphics->outputBAND.at(i).count(); j++)
		{
			if (graphics->oXBand[j] >= buildNumbers[0] && graphics->oXBand[j] <= buildNumbers[1])
			{
				if (params->zeroShift)
					tempCorrectionY.append(graphics->outputBAND.at(i).at(j) - graphics->fermi);
				else
					tempCorrectionY.append(graphics->outputBAND.at(i).at(j));
				tempCorrectionX.append(graphics->oXBand[j]- buildNumbers[0]);
				for (int ii=0; ii<graphics->kPoints.size(); ii++)
				{
					if (abs(graphics->oXBand[j] - buildNumbers[0] - graphics->kPoints[ii]) < 0.00001)
						tempCorrectionX[tempCorrectionX.size() - 1] = graphics->kPoints[ii];
				}
			}
		}
		newCurve->addData(tempCorrectionX, tempCorrectionY);
		tempCorrectionX.clear();
		tempCorrectionY.clear();
		newCurve->addData(qQNaN(), qQNaN());
	}
	newCurve->setPen(pen);

	customPlot->setGeometry(30, 30, params->drawRes, params->drawRes);
	customPlot->setMinimumSize(params->drawRes, params->drawRes);
	customPlot->setMaximumSize(params->drawRes, params->drawRes);

	customPlot->xAxis2->setVisible(true);
	customPlot->yAxis2->setVisible(true);
	customPlot->xAxis2->setTicks(false);
	customPlot->yAxis2->setTicks(false);
	customPlot->xAxis2->setTickLabels(false);
	customPlot->yAxis2->setTickLabels(false);


	QVector<double> TickValues;
	QVector<QString> TickLabels;

	QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
	customPlot->xAxis->setTicker(textTicker);
	QStringList kPointsList = kPoints.split(" ");

	for (int i=0; i< kPointsList.count(); i++)
	{
		for (int j = 0; j < symbols->map->count(); j++)
		{
			if (kPointsList[i].contains(symbols->map->keys().at(j)))
				kPointsList[i] = kPointsList[i].replace(symbols->map->keys().at(j), symbols->map->values().at(j));
		}
	}
	
	
	if (kPointsList.size()>0)
		textTicker->addTick(0, kPointsList.at(0));
	
	for (int i = 0; i < graphics->kPoints.count(); i++)
	{
		if (i+1 < kPointsList.count())
		{
			textTicker->addTick(graphics->kPoints.at(i), kPointsList.at(i + 1));
		}	
	}

	customPlot->xAxis->grid()->setVisible(false);
	customPlot->yAxis->grid()->setVisible(false);

	customPlot->xAxis->rescale(true);
	customPlot->yAxis->rescale(true);
	customPlot->setWindowTitle("Plot");

	newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
	for (int i = 0; i < graphics->kPoints.count(); i++)
	{
		if (graphics->kPoints.at(i)>= 0 && graphics->kPoints.at(i) <= buildNumbers[1] - buildNumbers[0])
		{
			
			newCurve->addData({ graphics->kPoints.at(i),graphics->kPoints.at(i) }, { -1000,1000 });
		}
			
		newCurve->addData(qQNaN(), qQNaN());
	}
	pen.setStyle(Qt::PenStyle::SolidLine);
	pen.setColor(Qt::black);
	pen.setWidthF(1);
	newCurve->setPen(pen);

	if (params->tab2ShowFermiLine == true)
	{
		pen.setStyle(Qt::PenStyle::DashLine);
		pen.setColor(params->tab2FermiLevel);
		pen.setWidthF(params->tab2FermiLevelWidth);
		newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
		if (params->zeroShift)
		{
			newCurve->addData({ 0, buildNumbers[1] - buildNumbers[0] }, { 0,0 });
		}
		else
			newCurve->addData({ 0, buildNumbers[1] - buildNumbers[0] }, { graphics->fermi,graphics->fermi });
		newCurve->setPen(pen);
	}

	customPlot->setFont(font);
	customPlot->xAxis->setTickLabelFont(font);
	customPlot->yAxis->setTickLabelFont(font);
	customPlot->xAxis->setLabelFont(font);
	customPlot->yAxis->setLabelFont(font);

	if (min != 0 || max != 0)
	{
		customPlot->yAxis->setRange(min, max);
	}

	font.setPointSize(font.pointSize() + 2);
	font.setBold(true);
	if (params->tab2PlotName != "")
	{
		for (int i = symbols->map->count() - 1; i >= 0; i--)
		{
			if (params->tab2PlotName.contains(symbols->map->keys().at(i)))
				params->tab2PlotName = params->tab2PlotName.replace(symbols->map->keys().at(i), symbols->map->values().at(i));
		}
		customPlot->plotLayout()->insertRow(0);
		customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, params->tab2PlotName, font));
	}

	if (params->tab2OxName != "")
	{
		for (int i = symbols->map->count() - 1; i >= 0; i--)
		{
			if(params->tab2OxName.contains(symbols->map->keys().at(i)))
				params->tab2OxName = params->tab2OxName.replace(symbols->map->keys().at(i), symbols->map->values().at(i));
		}
		customPlot->xAxis->setLabel(params->tab2OxName);
	}

	if (params->tab2OyName != "")
	{
		for (int i = symbols->map->count() - 1; i >= 0; i--)
		{
			if (params->tab2OyName.contains(symbols->map->keys().at(i)))
				params->tab2OyName = params->tab2OyName.replace(symbols->map->keys().at(i), symbols->map->values().at(i));
		}
		customPlot->yAxis->setLabel(params->tab2OyName);
	}


	customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));

	customPlot->setWindowTitle(title);
	customPlot->show();
	//customPlot->setAttribute(Qt::WA_DeleteOnClose);
}

void ZoneStructGraphBuilder::contextMenuRequest(QPoint pos)
{
	QMenu* menu = new QMenu(this);
	menu->setAttribute(Qt::WA_DeleteOnClose);
    menu->addAction(tr("Сохранить график"), this, SLOT(savePicture()));
    menu->addAction(tr("Настройки"), parent, SLOT(showPictureSettings()));
	menu->popup(customPlot->mapToGlobal(pos));
}

void ZoneStructGraphBuilder::savePicture()
{
	QString filenameOnly = "";
	auto fileFormats = tr("PNG file (*.png);;All Files (*)");
	switch (plotParams->preferFormat)
	{
	case 0:
		filenameOnly = customPlot->windowTitle() + ".png";
		fileFormats = tr("PNG file (*.png);;All Files (*)");
		break;
	case 1:
		filenameOnly = customPlot->windowTitle() + ".jpg";
		fileFormats = tr("JPG file (*.jpg);;All Files (*)");
		break;
	case 2:
		filenameOnly = customPlot->windowTitle() + ".bmp";
		fileFormats = tr("BMP file (*.bmp);All Files (*)");
		break;
	default:
		break;
	}

	QString fileName = QFileDialog::getSaveFileName(this,
		tr("Сохранить график"), settings->lastPath + filenameOnly,
		fileFormats);
	if (fileName != "")
	{
		double h = static_cast<double>(customPlot->height());
		double w = static_cast<double>(customPlot->width());
		double scale = plotParams->drawScale / (h > w ? h / 600.0 : w / 600.0) / 2;
		bool success = false;
		switch (plotParams->preferFormat)
		{
		case 0:
			success = customPlot->savePng(fileName, customPlot->width(), customPlot->height(), scale);
			break;
		case 1:
			success = customPlot->saveJpg(fileName, customPlot->width(), customPlot->height(), scale, plotParams->drawQuality);
			break;
		case 2:
			success = customPlot->saveBmp(fileName, customPlot->width(), customPlot->height(), scale);
			break;
		default:
			break;
		}


		QFileInfo fileinfo(fileName);
		settings->UpdatePath(fileinfo.absolutePath());
		if (success == false)
		{
            QMessageBox::critical(this, tr("Ошибка сохранения"), tr("Не удалось сохранить изображение!"));
			return;
		}
	}
}

bool ZoneStructGraphBuilder::isClosed()
{
	if (customPlot->window()->effectiveWinId() == 0)
	{
		return true;
	}
	else
		return false;
}

ZoneStructGraphBuilder::~ZoneStructGraphBuilder()
{
	customPlot->clearGraphs();
	customPlot->clearItems();
	customPlot->clearPlottables();
	delete customPlot;
}


