// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "zonegraph.h"

ZoneGraph::ZoneGraph(SettingsKeeper* settings, const QString& title, PlotParameters* plotParams, const QFont font, QWidget* parent)
: GraphBuilder(settings, title, plotParams, font, parent)
{
	plotType = 3;
}

void ZoneGraph::draw(BandData* graphics, const double min, const double max, const QString kPoints,
	double buildNumbers[2], MathSymbols* symbols)
{
	QPen pen;

	pen.setStyle(plotParams->tab2PlotParams->at(0).style);
	pen.setColor(plotParams->tab2PlotParams->at(0).color);
	pen.setWidthF(plotParams->tab2PlotParams->at(0).width);
	QCPCurve* newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);

	for (int i = 0; i < graphics->outputBAND.count(); i++)
	{

		QVector<double> tempCorrectionY;
		QVector<double> tempCorrectionX;
		for (int j = 0; j < graphics->outputBAND.at(i).count(); j++)
		{
			if (graphics->oXBand[j] >= buildNumbers[0] && graphics->oXBand[j] <= buildNumbers[1])
			{
				if (plotParams->tab2zeroShift)
					tempCorrectionY.append(graphics->outputBAND.at(i).at(j) - graphics->fermi);
				else
					tempCorrectionY.append(graphics->outputBAND.at(i).at(j));
				tempCorrectionX.append(graphics->oXBand[j] - buildNumbers[0]);
				for (int ii = 0; ii < graphics->kPoints.size(); ii++)
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

	customPlot->setGeometry(30, 30, plotParams->drawRes, plotParams->drawRes);
	customPlot->setMinimumSize(plotParams->drawRes, plotParams->drawRes);
	customPlot->setMaximumSize(plotParams->drawRes, plotParams->drawRes);


	QVector<double> tickValues;
	QVector<QString> tickLabels;

	const QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
	customPlot->xAxis->setTicker(textTicker);
	QStringList kPointsList = kPoints.split(" ");

	for (int i = 0; i < kPointsList.count(); i++)
	{
		kPointsList[i] = symbols->adaptString(kPointsList[i]);
	}


	if (!kPointsList.empty())
		textTicker->addTick(0, kPointsList.at(0));

	for (int i = 0; i < graphics->kPoints.count(); i++)
	{
		if (i + 1 < kPointsList.count())
		{
			textTicker->addTick(graphics->kPoints.at(i), kPointsList.at(i + 1));
		}
	}

	customPlot->xAxis->grid()->setVisible(false);
	customPlot->yAxis->grid()->setVisible(false);

	customPlot->xAxis->rescale(true);
	customPlot->yAxis->rescale(true);
	customPlot->setWindowTitle(STR_GraphTitle_PlotDefaultNameZoneStruct);

	newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
	for (int i = 0; i < graphics->kPoints.count(); i++)
	{
		if (graphics->kPoints.at(i) >= 0 && graphics->kPoints.at(i) <= buildNumbers[1] - buildNumbers[0])
		{

			newCurve->addData({ graphics->kPoints.at(i),graphics->kPoints.at(i) }, { -1000,1000 });
		}

		newCurve->addData(qQNaN(), qQNaN());
	}
	pen.setStyle(Qt::PenStyle::SolidLine);
	pen.setColor(Qt::black);
	pen.setWidthF(1);
	newCurve->setPen(pen);

	if (plotParams->tab2ShowFermiLine == true)
	{
		pen.setStyle(Qt::PenStyle::DashLine);
		pen.setColor(plotParams->tab2FermiLevel);
		pen.setWidthF(plotParams->tab2FermiLevelWidth);
		newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
		if (plotParams->tab2zeroShift)
		{
			newCurve->addData({ 0, buildNumbers[1] - buildNumbers[0] }, { 0,0 });
		}
		else
			newCurve->addData({ 0, buildNumbers[1] - buildNumbers[0] }, { graphics->fermi,graphics->fermi });
		newCurve->setPen(pen);
	}

	if (min != 0 || max != 0)
	{
		customPlot->yAxis->setRange(min, max);
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
		customPlot->xAxis->setLabel(symbols->adaptString(plotParams->tab2OxName));
	}

	if (plotParams->tab2OyName != "")
	{
		customPlot->yAxis->setLabel(symbols->adaptString(plotParams->tab2OyName));
	}

	this->show();
}
