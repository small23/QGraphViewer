#pragma once

#include "banddata.h"
#include "graphbuilder.h"
#include "mathsymbols.h"

class ZoneGraph final : public GraphBuilder
{
	

public:
	ZoneGraph(SettingsKeeper* settings, const QString& title, PlotParameters* plotParams, QFont font, QWidget* parent);
	virtual void draw(BandData* graphics, double min, double max, QString kPoints,
		double buildNumbers[2],  MathSymbols* symbols);
};
