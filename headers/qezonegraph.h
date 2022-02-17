#pragma once
#include "qezonedata.h"
#include "graphbuilder.h"
#include "mathsymbols.h"
#include <QStandardItemModel>
#include <QStandardItem>

class QeZoneGraph final : public GraphBuilder
{
public:
	QeZoneGraph(SettingsKeeper* settings, const QString& title, PlotParameters* plotParams, QFont font, QWidget* parent);
	void QeZoneGraph::draw(QeZoneData* graphics, const double min, const double max, const QStandardItemModel* kPoints, MathSymbols* symbols);
};
