#pragma once

#include "banddata.h"
#include "graphbuilder.h"
#include "mathsymbols.h"

class DosGraph final : public GraphBuilder
{
	Q_OBJECT

public:
	DosGraph(SettingsKeeper* settings, const QString& title, PlotParameters* plotParams, QFont font, QWidget* parent);
	virtual void draw(BandData* graphics, double borders[4], const int angle, MathSymbols* symbols,
		const int currentGraphic);
private:
	void drawData(QVector<QVector<double>> data, const QVector<double>& axis, int angle,
	              int paramsShift, bool* showed) const;
};
