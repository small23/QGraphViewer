#include "dosgraphbuilder.h"

DOSGraphBuilder::DOSGraphBuilder(BandData* graphics, double borders[4], PlotParameters* params, QFont font, const int angle, SettingsKeeper* settings, MathSymbols *symbols, const int currentGraphic, QWidget* parent) : QWidget(parent)
{
	this->settings = settings;
	customPlot = new QCustomPlot();
	QCPCurve* newCurve;
	this->plotParams = params;
	this->parent = parent;
	QPen pen;

	if (params->zeroShift)
	{
		for (int ii = 0; ii < graphics->oXCohp.count(); ii++)
		{
			graphics->oXCohp[ii] -= graphics->fermi;
		}
		for (int ii = 0; ii < graphics->oXCoop.count(); ii++)
		{
			graphics->oXCoop[ii] -= graphics->fermi;
		}
		for (int ii = 0; ii < graphics->oXDoss.count(); ii++)
		{
			graphics->oXDoss[ii] -= graphics->fermi;
		}
	}

	QVector<double> tempArray;
	bool showed = false;

	drawData(graphics->outputCOHP, graphics->oXCohp, params, angle, 0, &showed);
	drawData(graphics->outputCOOP, graphics->oXCoop, params, angle, graphics->outputCOHP.count(), &showed);
	drawData(graphics->outputDOSS, graphics->oXDoss, params, angle, graphics->outputCOHP.count() + graphics->outputCOOP.count(), &showed);

	if (!showed)
	{
		params->tab2PlotParams->data()[currentGraphic].show = true;
		drawData(graphics->outputCOHP, graphics->oXCohp, params, angle, 0, &showed);
		drawData(graphics->outputCOOP, graphics->oXCoop, params, angle, graphics->outputCOHP.count(), &showed);
		drawData(graphics->outputDOSS, graphics->oXDoss, params, angle, graphics->outputCOHP.count() + graphics->outputCOOP.count(), &showed);
		params->tab2PlotParams->data()[currentGraphic].show = false;
	}
	
	customPlot->setGeometry(30, 30, params->drawRes, params->drawRes);
	customPlot->setMinimumSize(params->drawRes, params->drawRes);
	customPlot->setMaximumSize(params->drawRes, params->drawRes);

	QVector<double> tickValues;
	QVector<QString> tickLabels;

	customPlot->xAxis->grid()->setVisible(false);
	customPlot->yAxis->grid()->setVisible(false);

	customPlot->xAxis->rescale(true);
	customPlot->yAxis->rescale(true);
    customPlot->setWindowTitle(tr("Plot"));

	if (params->tab2ShowFermiLine == true)
	{
		newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
		if (angle > 0)
		{
			if (params->zeroShift)
				newCurve->addData( { -1000000,10000000 }, { 0,0 });
			else
				newCurve->addData( { -1000000,10000000 }, { graphics->fermi,graphics->fermi });
		}
		else
		{
			if (params->zeroShift)
				newCurve->addData({ 0,0 }, { -1000000,10000000 });
			else
				newCurve->addData({ graphics->fermi,graphics->fermi }, { -1000000,10000000 });
		}
		
		pen.setStyle(Qt::PenStyle::DashLine);
		pen.setColor(params->tab2FermiLevel);
		pen.setWidthF(params->tab2FermiLevelWidth);
		newCurve->setPen(pen);
	}

	double bordersNew[2] = { graphics->borders[0],graphics->borders[1]};

	if (borders[0] != 0 || borders[1] != 0)
	{
		bordersNew[0] = borders[0];
		bordersNew[1] = borders[1];
	}
		
	
	newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
	if (params->zeroShift)
	{
		if (angle > 0)
			newCurve->addData({ 0,0 }, { bordersNew[0] - graphics->fermi,bordersNew[1] - graphics->fermi });
		else
			newCurve->addData({ bordersNew[0]-graphics->fermi,bordersNew[1] - graphics->fermi }, { 0,0 });
	}
	else
	{
		if (angle > 0)
			newCurve->addData({ 0,0 }, { bordersNew[0],bordersNew[1] });
		else
			newCurve->addData({ bordersNew[0],bordersNew[1] }, { 0,0 });
	}

	pen.setStyle(Qt::PenStyle::SolidLine);
	pen.setColor(Qt::black);
	pen.setWidthF(1);
	newCurve->setPen(pen);

	customPlot->setFont(font);
	customPlot->xAxis->setTickLabelFont(font);
	customPlot->yAxis->setTickLabelFont(font);
	
	if (angle==0)
	{
		if (borders[2] != 0 || borders[3] != 0)
			customPlot->yAxis->setRange(borders[2], borders[3]);

		if (borders[0] != 0 || borders[1] != 0)
			customPlot->xAxis->setRange(borders[0], borders[1]);
	}
	else
	{
		if (borders[2] != 0 || borders[3] != 0)
			customPlot->xAxis->setRange(borders[2], borders[3]);

		if (borders[0] != 0 || borders[1] != 0)
			customPlot->yAxis->setRange(borders[0], borders[1]);
	}



	customPlot->setFont(font);
	customPlot->xAxis->setTickLabelFont(font);
	customPlot->yAxis->setTickLabelFont(font);
	customPlot->xAxis->setLabelFont(font);
	customPlot->yAxis->setLabelFont(font);

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
			if (params->tab2OxName.contains(symbols->map->keys().at(i)))
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

	customPlot->xAxis2->setVisible(true);
	customPlot->yAxis2->setVisible(true);
	customPlot->xAxis2->setTicks(false);
	customPlot->yAxis2->setTicks(false);
	customPlot->xAxis2->setTickLabels(false);
	customPlot->yAxis2->setTickLabels(false);

	if (params->tab2OxTicks == true)
		customPlot->xAxis->setTicks(true);
	else
		customPlot->xAxis->setTicks(false);

	if (params->tab2OyTicks == true)
		customPlot->yAxis->setTicks(true);
	else
		customPlot->yAxis->setTicks(false);

	if (angle == 2)
		customPlot->xAxis->setRangeReversed(true);

	customPlot->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(customPlot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
	customPlot->show();
	customPlot->setAttribute(Qt::WA_DeleteOnClose);
}

void DOSGraphBuilder::drawData(QVector<QVector<double>> data, const QVector<double>& axis, PlotParameters* params, const int angle, const int paramsShift, bool* showed) const
{
	QPen pen;
	QVector<double> y;
	
	for (int i = 0; i < data.count(); i++)
	{
		y.clear();
		if (params->tab2PlotParams->at(i + paramsShift).show == true)
		{
			for (int ii = 0; ii < data.at(i).count(); ii++)
			{
				if (angle == 1)
					y.append(data.data()[i][ii] * params->tab2PlotParams->at(i + paramsShift).multiplier);
				else if (angle == 2)
					y.append(data.data()[i][ii] * params->tab2PlotParams->at(i + paramsShift).multiplier);
				else
					y.append(data.data()[i][ii] * params->tab2PlotParams->at(i + paramsShift).multiplier);
				if (params->tab2FxInverse == true)
					y.data()[ii] =- y.data()[ii];
			}
			
			QCPCurve* newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
			switch (angle)
			{
			case 0:
				newCurve->addData(axis, y);
				break;
			default:
				newCurve->addData(y, axis);
				break;
			}
			
			pen.setStyle(params->tab2PlotParams->at(i + paramsShift).style);
			pen.setColor(params->tab2PlotParams->at(i + paramsShift).color);
			pen.setWidthF(params->tab2PlotParams->at(i + paramsShift).width);
			newCurve->setPen(pen);
			*showed = true;
		}
	}
}


void DOSGraphBuilder::contextMenuRequest(const QPoint pos)
{
	QMenu* menu = new QMenu(this);
	menu->setAttribute(Qt::WA_DeleteOnClose);
	menu->addAction("Сохранить график", this, SLOT(savePicture()));
	menu->addAction("Настройки", parent, SLOT(showPictureSettings()));
	menu->popup(customPlot->mapToGlobal(pos));
}

void DOSGraphBuilder::savePicture()
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

	const QString fileName = QFileDialog::getSaveFileName(this,
	                                                      tr("Сохранить график"), settings->lastPath+filenameOnly,
	                                                      fileFormats);
	if (fileName != "")
	{
		const double h = static_cast<double>(customPlot->height());
		const double w = static_cast<double>(customPlot->width());
		const double scale = plotParams->drawScale / (h > w ? h / 600.0 : w / 600.0) / 2;
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

		const QFileInfo fileinfo(fileName);
		settings->updatePath(fileinfo.absolutePath());
		if (success == false)
		{
			QMessageBox::critical(this, "Ошибка сохранения", "Не удалось сохранить изображение!");
		}
	}
}
