// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "dosgraph.h"

DosGraph::DosGraph(SettingsKeeper* settings, const QString& title, PlotParameters* plotParams, const QFont font, QWidget* parent)
: GraphBuilder(settings, title, plotParams, font, parent)
{
	plotType = 2;
}

void DosGraph::draw(BandData* graphics, double borders[4], const int angle,
	MathSymbols* symbols, const int currentGraphic)
{
	QCPCurve* newCurve;
	QPen pen;

	if (plotParams->tab2zeroShift)
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

	drawData(graphics->outputCOHP, graphics->oXCohp, angle, 0, &showed);
	drawData(graphics->outputCOOP, graphics->oXCoop, angle, graphics->outputCOHP.count(), &showed);
	drawData(graphics->outputDOSS, graphics->oXDoss, angle, graphics->outputCOHP.count() + graphics->outputCOOP.count(), &showed);

	if (!showed)
	{
		plotParams->tab2PlotParams->data()[currentGraphic].show = true;
		drawData(graphics->outputCOHP, graphics->oXCohp, angle, 0, &showed);
		drawData(graphics->outputCOOP, graphics->oXCoop, angle, graphics->outputCOHP.count(), &showed);
		drawData(graphics->outputDOSS, graphics->oXDoss, angle, graphics->outputCOHP.count() + graphics->outputCOOP.count(), &showed);
		plotParams->tab2PlotParams->data()[currentGraphic].show = false;
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

	if (plotParams->tab2ShowFermiLine == true)
	{
		newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
		if (angle > 0)
		{
			if (plotParams->tab2zeroShift)
				newCurve->addData({ -1000000,10000000 }, { 0,0 });
			else
				newCurve->addData({ -1000000,10000000 }, { graphics->fermi,graphics->fermi });
		}
		else
		{
			if (plotParams->tab2zeroShift)
				newCurve->addData({ 0,0 }, { -1000000,10000000 });
			else
				newCurve->addData({ graphics->fermi,graphics->fermi }, { -1000000,10000000 });
		}

		pen.setStyle(Qt::PenStyle::DashLine);
		pen.setColor(plotParams->tab2FermiLevel);
		pen.setWidthF(plotParams->tab2FermiLevelWidth);
		newCurve->setPen(pen);
	}

	double bordersNew[2] = { graphics->borders[0],graphics->borders[1] };

	if (borders[0] != 0 || borders[1] != 0)
	{
		bordersNew[0] = borders[0];
		bordersNew[1] = borders[1];
	}


	newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
	if (plotParams->tab2zeroShift)
	{
		if (angle > 0)
			newCurve->addData({ 0,0 }, { bordersNew[0] - graphics->fermi,bordersNew[1] - graphics->fermi });
		else
			newCurve->addData({ bordersNew[0] - graphics->fermi,bordersNew[1] - graphics->fermi }, { 0,0 });
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

	if (angle == 0)
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

	font.setPointSize(font.pointSize() + 2);
	font.setBold(true);
	if (plotParams->tab2PlotName != "")
	{
		customPlot->plotLayout()->insertRow(0);
		customPlot->plotLayout()->addElement(0, 0, new QCPTextElement(customPlot, symbols->adaptString(plotParams->tab2PlotName), font));
	}

	if (plotParams->tab2OxName != "")
	{
		if (angle == 0)
			customPlot->xAxis->setLabel(symbols->adaptString(plotParams->tab2OxName));
		else
			customPlot->yAxis->setLabel(symbols->adaptString(plotParams->tab2OxName));
	}

	if (plotParams->tab2OyName != "")
	{
		if (angle == 0)
			customPlot->yAxis->setLabel(symbols->adaptString(plotParams->tab2OyName));
		else
			customPlot->xAxis->setLabel(symbols->adaptString(plotParams->tab2OyName));
	}


	if (plotParams->tab2OxTicks == true)
		customPlot->xAxis->setTicks(true);
	else
		customPlot->xAxis->setTicks(false);

	if (plotParams->tab2OyTicks == true)
		customPlot->yAxis->setTicks(true);
	else
		customPlot->yAxis->setTicks(false);

	if (angle == 2)
		customPlot->xAxis->setRangeReversed(true);

	customPlot->show();
}

void DosGraph::drawData(QVector<QVector<double>> data, const QVector<double>& axis, const int angle, const int paramsShift, bool* showed) const
{
	QPen pen;
	QVector<double> y;

	for (int i = 0; i < data.count(); i++)
	{
		y.clear();
		if (plotParams->tab2PlotParams->at(i + paramsShift).show == true)
		{
			for (int ii = 0; ii < data.at(i).count(); ii++)
			{
				if (angle == 1)
					y.append(data.data()[i][ii] * plotParams->tab2PlotParams->at(i + paramsShift).multiplier);
				else if (angle == 2)
					y.append(data.data()[i][ii] * plotParams->tab2PlotParams->at(i + paramsShift).multiplier);
				else
					y.append(data.data()[i][ii] * plotParams->tab2PlotParams->at(i + paramsShift).multiplier);
				if (plotParams->tab2FxInverse == true)
					y.data()[ii] = -y.data()[ii];
			}

			QCPCurve* newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);

			if (angle==0)
				newCurve->addData(axis, y);
			else
				newCurve->addData(y, axis);


			pen.setStyle(plotParams->tab2PlotParams->at(i + paramsShift).style);
			pen.setColor(plotParams->tab2PlotParams->at(i + paramsShift).color);
			pen.setWidthF(plotParams->tab2PlotParams->at(i + paramsShift).width);
			newCurve->setPen(pen);
			*showed = true;
		}
	}
}