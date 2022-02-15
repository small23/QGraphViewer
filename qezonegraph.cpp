#include "qezonegraph.h"

QeZoneGraph::QeZoneGraph(SettingsKeeper* settings, const QString& title, PlotParameters* plotParams, const QFont font, QWidget* parent)
	: GraphBuilder(settings, title, plotParams, font, parent)
{
	plotType = 3;
}

void QeZoneGraph::draw(QeZoneData* graphics, const double min, const double max, const QString kPoints,
 MathSymbols* symbols)
{
	QPen pen;

	pen.setStyle(plotParams->tab2PlotParams->at(0).style);
	pen.setColor(plotParams->tab2PlotParams->at(0).color);
	pen.setWidthF(plotParams->tab2PlotParams->at(0).width);
	QCPCurve* newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);

	for (int i = 0; i < graphics->outputY.count(); i++)
	{

		QVector<double> tempCorrectionY;
		QVector<double> tempCorrectionX;
		for (int j = 0; j < graphics->outputY.at(i).count(); j++)
		{
			if (graphics->outputX[j])
			{

				tempCorrectionY.append(graphics->outputY.at(i).at(j) + plotParams->tab5DOSShift);
				tempCorrectionX.append(graphics->outputX[j]);
			}
		}
		newCurve->addData(tempCorrectionX, tempCorrectionY);
		tempCorrectionX.clear();
		tempCorrectionY.clear();
		newCurve->addData(qQNaN(), qQNaN());
	}
	newCurve->setPen(pen);
	this->compareScale = 600.0/900.0;
	customPlot->setGeometry(30, 30, plotParams->drawRes, plotParams->drawRes * 0.66);
	customPlot->setMinimumSize(plotParams->drawRes, plotParams->drawRes * 0.66);
	customPlot->setMaximumSize(plotParams->drawRes, plotParams->drawRes * 0.66);


	QVector<double> tickValues;
	QVector<QString> tickLabels;

	const QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
	customPlot->xAxis->setTicker(textTicker);
	QStringList kPointsList = kPoints.split(" ");

	for (int i = 0; i < kPointsList.count(); i++)
	{
		kPointsList[i] = symbols->adaptString(kPointsList[i]);
	}

	/*
	if (!kPointsList.empty())
		textTicker->addTick(0, kPointsList.at(0));

	for (int i = 0; i < graphics->kPoints.count(); i++)
	{
		if (i + 1 < kPointsList.count())
		{
			textTicker->addTick(graphics->kPoints.at(i), kPointsList.at(i + 1));
		}
	}
	*/
	customPlot->xAxis->grid()->setVisible(false);
	customPlot->yAxis->grid()->setVisible(false);

	customPlot->xAxis->rescale(true);
	customPlot->yAxis->rescale(true);
	customPlot->setWindowTitle(STR_GraphTitle_PlotDefaultNameZoneStruct);

	/*
	newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
	for (int i = 0; i < graphics->kPoints.count(); i++)
	{
		if (graphics->kPoints.at(i) >= 0 && graphics->kPoints.at(i) <= buildNumbers[1] - buildNumbers[0])
		{

			newCurve->addData({ graphics->kPoints.at(i),graphics->kPoints.at(i) }, { -1000,1000 });
		}

		newCurve->addData(qQNaN(), qQNaN());
	}
	*/
	pen.setStyle(Qt::PenStyle::SolidLine);
	pen.setColor(Qt::black);
	pen.setWidthF(1);
	newCurve->setPen(pen);
	/*
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
	*/
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
