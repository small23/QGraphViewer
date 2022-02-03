#pragma once
#include "graphbuilder.h"
#include "qesurfdata.h"

class QEContourGraph final :GraphBuilder
{
public:
	QEContourGraph(SettingsKeeper* settings, const QString& title, PlotParameters* plotParams, QFont font, QWidget* parent = nullptr);
	virtual void draw(QeSurfData* data);
	void drawSurface(QeSurfData* surfData) const;
	void drawDataIsolines(std::vector<MarchingSquares::levelPaths> result, double* hslA, double* hslB,
	                      const double* hslAStep, const double* hslBStep, const QVector<double>& oXTemp,
	                      const QVector<double>& oYTemp, bool shiftA, bool shiftB, int hslABorder, int hslBBorder,
	                      int angle, double stepX, double stepY) const;
};
