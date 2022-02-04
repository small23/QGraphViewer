// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "qegraph.h"

QeGraph::QeGraph(SettingsKeeper* settings, const QString& title, PlotParameters* plotParams, QFont font,
	QWidget* parent) : GraphBuilder(settings, title, plotParams, font, parent)
{

}

void QeGraph::draw(QeDos* data, MathSymbols* symbols, const int currentGraphic, int angle)
{
	QCPCurve* newCurve;
	QPen pen;
	bool isShowed = false;
	drawData(data, angle, &isShowed);
	if (!isShowed)
	{
		int lineCounter = 0;
		for (int file = 0; file < data->pdos.count(); file++) //file count
		{
			for (int i = 1; i < data->pdos[file][0].size(); i++) //Count collums of data (line count)
			{
				if (lineCounter==currentGraphic)
				{
					plotParams->tab5PlotParams->data()[lineCounter].show = true;
					drawData(data, angle, &isShowed);
					plotParams->tab5PlotParams->data()[lineCounter].show = false;
				}
				lineCounter++;
			}
		}
		
	}
	
	customPlot->setGeometry(30, 30, plotParams->drawRes, plotParams->drawRes);
	customPlot->setMinimumSize(plotParams->drawRes, plotParams->drawRes);
	customPlot->setMaximumSize(plotParams->drawRes, plotParams->drawRes);

	QVector<double> tickValues;
	QVector<QString> tickLabels;

	customPlot->xAxis->grid()->setVisible(false);
	customPlot->yAxis->grid()->setVisible(false);

	customPlot->xAxis->rescale(true);
	customPlot->yAxis->rescale(true);

	newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
	if (plotParams->tab2zeroShift)
	{
		if (angle > 0)
			newCurve->addData({ 0,0 }, { -99999,99999 });
		else
			newCurve->addData({ -99999,99999 }, { 0,0 });
	}
	else
	{
		if (angle > 0)
			newCurve->addData({ 0,0 }, { -99999,99999 });
		else
			newCurve->addData({ -99999,99999 }, { 0,0 });
	}

	pen.setStyle(Qt::PenStyle::SolidLine);
	pen.setColor(Qt::black);
	pen.setWidthF(1);
	newCurve->setPen(pen);


	if (plotParams->tab5ShowFermiLine == true)
	{
		newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
		if (angle > 0)
		{
			newCurve->addData({ -1000000,10000000 }, {plotParams->tab5FermiLevel,plotParams->tab5FermiLevel});
		}
		else
		{
			newCurve->addData({ plotParams->tab5FermiLevel,plotParams->tab5FermiLevel}, { -1000000,10000000 });
		}

		pen.setStyle(Qt::PenStyle::DashLine);
		pen.setColor(plotParams->tab5FermiLevelColor);
		pen.setWidthF(plotParams->tab5FermiLevelWidth);
		newCurve->setPen(pen);
	}

	
	if (angle == 0)
	{
		if (plotParams->tab5yMin != 0 || plotParams->tab5yMax != 0)
			customPlot->yAxis->setRange(plotParams->tab5yMin, plotParams->tab5yMax);

		if (plotParams->tab5xMin != 0 || plotParams->tab5xMax != 0)
			customPlot->xAxis->setRange(plotParams->tab5xMin, plotParams->tab5xMax);
	}
	else
	{
		if (plotParams->tab5yMin != 0 || plotParams->tab5yMax != 0)
			customPlot->xAxis->setRange(plotParams->tab5yMin, plotParams->tab5yMax);

		if (plotParams->tab5xMin != 0 || plotParams->tab5xMax != 0)
			customPlot->yAxis->setRange(plotParams->tab5xMin, plotParams->tab5xMax);
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
		if (angle == 0)
			customPlot->xAxis->setLabel(symbols->adaptString(plotParams->tab5OxName));
		else
			customPlot->yAxis->setLabel(symbols->adaptString(plotParams->tab5OxName));
	}

	if (plotParams->tab5OyName != "")
	{
		if (angle == 0)
			customPlot->yAxis->setLabel(symbols->adaptString(plotParams->tab5OyName));
		else
			customPlot->xAxis->setLabel(symbols->adaptString(plotParams->tab5OyName));
	}


	if (plotParams->tab5OxTicks == true)
		customPlot->xAxis->setTicks(true);
	else
		customPlot->xAxis->setTicks(false);

	if (plotParams->tab5OyTicks == true)
		customPlot->yAxis->setTicks(true);
	else
		customPlot->yAxis->setTicks(false);

	if (angle == 2)
		customPlot->xAxis->setRangeReversed(true);
	this->show();
}

void QeGraph::drawData(QeDos* data, int angle, bool* isShowed)
{
	QCPCurve* newCurve;
	QPen pen;
	QVector<double> x;
	QVector<double> y;
	int lineCounter = 0;
	for (int file = 0; file < data->pdos.count(); file++) //file count
	{
		for (int i = 1; i < data->pdos[file][0].size(); i++) //Count collums of data (line count)
		{
			if (plotParams->tab5PlotParams->at(lineCounter).show)
			{
				x.clear();
				y.clear();
				for (int j = 0; j < data->pdos[file].size(); j++) //Line size (point number)
				{
					x.append(data->pdos[file][j][0] + plotParams->tab5DOSShift);
					y.append(data->pdos[file][j][i] * plotParams->tab5PlotParams->at(lineCounter).multiplier);
				}
				QCPCurve* newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
				if (angle == 0)
					newCurve->addData(x, y);
				else
				{
					newCurve->addData(y, x);
				}
				pen.setStyle(plotParams->tab5PlotParams->at(lineCounter).style);
				pen.setColor(plotParams->tab5PlotParams->at(lineCounter).color);
				pen.setWidthF(plotParams->tab5PlotParams->at(lineCounter).width);
				newCurve->setPen(pen);
				*isShowed = true;
			}
			lineCounter++;

		}
	}
}