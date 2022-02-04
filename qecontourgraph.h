#pragma once
#include "graphbuilder.h"
#include "qesurfdata.h"

class QEContourGraph final :GraphBuilder
{
public:
	QEContourGraph(SettingsKeeper* settings, const QString& title, PlotParameters* plotParams, QFont font, QWidget* parent = nullptr);
	virtual void draw(QeSurfData* data);
	void drawSurface(QeSurfData* surfData) const;
};
