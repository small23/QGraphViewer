#include "qegraph.h"

QeGraph::QeGraph(SettingsKeeper* settings, const QString& title, PlotParameters* plotParams, QFont font,
	QWidget* parent) : GraphBuilder(settings, title, plotParams, font, parent)
{

}

void QeGraph::draw(QeDos* data)
{
	QCPCurve* newCurve;
	QPen pen;
	newCurve = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
	double xmin = 999999999999;
	double xmax = -99999999999;
	double ymin = 999999999999;
	double ymax = -99999999999;

	for (int i=1; i<data->pdos[0][0].size(); i++)
	{
		for (int j=0; j<data->pdos[0].size(); j++)
		{
			newCurve->addData(data->pdos[0][j][0], data->pdos[0][j][i]);
			if (xmin > data->pdos[0][j][0])
				xmin = data->pdos[0][j][0];
			if (xmax < data->pdos[0][j][0])
				xmax = data->pdos[0][j][0];
			if (ymin > data->pdos[0][j][i])
				ymin = data->pdos[0][j][i];
			if (ymax < data->pdos[0][j][i])
				ymax = data->pdos[0][j][i];
		}
		newCurve->addData(qQNaN(), qQNaN());
	}
	customPlot->xAxis->setRange(xmin, xmax);
	customPlot->yAxis->setRange(ymin, ymax);
	customPlot->show();
}

