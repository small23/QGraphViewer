#include "qezonegraph.h"

QeZoneGraph::QeZoneGraph(SettingsKeeper* settings, const QString& title, PlotParameters* plotParams, const QFont font, QWidget* parent)
	: GraphBuilder(settings, title, plotParams, font, parent)
{
	plotType = 3;
}

void QeZoneGraph::draw(QeZoneData* graphics, const double min, const double max, const QStandardItemModel* kPoints,
	MathSymbols* symbols)
{
	QPen pen;

	pen.setStyle(plotParams->tab5PlotParams->at(0).style);
	pen.setColor(plotParams->tab5PlotParams->at(0).color);
	pen.setWidthF(plotParams->tab5PlotParams->at(0).width);
	QCPCurve* newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);

	for (int i = 0; i < graphics->outputY.count(); i++)
	{
		QVector<double> tempCorrectionY;
		for (int j = 0; j < graphics->outputY.at(i).count(); j++)
		{
			tempCorrectionY.append(graphics->outputY.at(i).at(j) * plotParams->tab5PlotParams->at(0).multiplier + plotParams->tab5DOSShift);
		}
		newCurve->addData(graphics->outputX, tempCorrectionY);
		tempCorrectionY.clear();
		newCurve->addData(qQNaN(), qQNaN());
	}

	newCurve->setPen(pen);
	this->compareScale = this->plotParams->drawRes / (this->plotParams->drawRes * 1.5);
	customPlot->setGeometry(30, 30, plotParams->drawRes, plotParams->drawRes * this->compareScale);
	customPlot->setMinimumSize(plotParams->drawRes, plotParams->drawRes * this->compareScale);
	customPlot->setMaximumSize(plotParams->drawRes, plotParams->drawRes * this->compareScale);


	QVector<double> tickValues;
	QVector<QString> tickLabels;

	const QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
	customPlot->xAxis->setTicker(textTicker);

	customPlot->xAxis->grid()->setVisible(false);
	customPlot->yAxis->grid()->setVisible(false);


	customPlot->yAxis->rescale(true);
	customPlot->setWindowTitle(STR_GraphTitle_PlotDefaultNameZoneStruct);

	for (int i = 0; i < kPoints->rowCount() - 1; i++)
	{
		bool ok = false;
		QStandardItem* item;
		QVector<double> vector;
		for (int j = 1; j < 4; j++)
		{
			item = kPoints->item(i, j);
			if (item != nullptr)
			{
				double value = item->text().toDouble(&ok);
				if (!ok)
					break;
				vector.append(value);
			}
			else
			{
				delete customPlot;
				delete vbl;
				this->destroy();
				this->deleteLater();
				return;
			}
		}
		if(ok)
		{
			item = kPoints->item(i, 0);
			QString name;
			if (item != nullptr)
			{
				name = item->text();
			}
			else
			{
				delete customPlot;
				delete vbl;
				this->destroy();
				this->deleteLater();
				return;
			}
			for (int j = 0; j < graphics->originVector.size(); j++)
			{
				if (graphics->originVector[j][0] != vector[0])
					continue;
				if (graphics->originVector[j][1] != vector[1])
					continue;
				if (graphics->originVector[j][2] != vector[2])
					continue;
				tickValues.append(graphics->outputX[j]);
				tickLabels.append(name);
			}
		}
		
	}

	newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
	for (int i = 0; i < tickValues.count(); i++)
	{
		textTicker->addTick(tickValues[i], tickLabels[i]);
		newCurve->addData({ tickValues[i],tickValues[i] }, { -1000,1000 });
		newCurve->addData(qQNaN(), qQNaN());
	}
	pen.setStyle(Qt::PenStyle::SolidLine);
	pen.setColor(Qt::black);
	pen.setWidthF(1);
	newCurve->setPen(pen);

	customPlot->xAxis->rescale(true);
	if (min != 0 || max != 0)
		customPlot->yAxis->setRange(min, max);

	newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
	newCurve->addData({ -99999,99999 }, { 0,0 });
	pen.setStyle(Qt::PenStyle::SolidLine);
	pen.setColor(Qt::black);
	pen.setWidthF(1);
	newCurve->setPen(pen);

	pen.setStyle(Qt::PenStyle::SolidLine);
	pen.setColor(Qt::black);
	pen.setWidthF(1);
	newCurve->setPen(pen);

	if (plotParams->tab5ShowFermiLine == true)
	{
		newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);

		newCurve->addData({ plotParams->tab5FermiLevel,plotParams->tab5FermiLevel }, { -1000000,10000000 });


		pen.setStyle(Qt::PenStyle::DashLine);
		pen.setColor(plotParams->tab5FermiLevelColor);
		pen.setWidthF(plotParams->tab5FermiLevelWidth);
		newCurve->setPen(pen);
	}

	if (min != 0 || max != 0)
	{
		customPlot->yAxis->setRange(min, max);
	}

	font.setPointSize(font.pointSize() + 2);
	font.setBold(true);
	if (plotParams->tab5PlotName != "")
	{
		customPlot->plotLayout()->insertRow(0);
		customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, symbols->adaptString(plotParams->tab5PlotName), font));
	}

	if (plotParams->tab5OxName != "")
	{
		customPlot->xAxis->setLabel(symbols->adaptString(plotParams->tab5OxName));
	}

	if (plotParams->tab5OyName != "")
	{
		customPlot->yAxis->setLabel(symbols->adaptString(plotParams->tab5OyName));
	}

	this->show();
}
