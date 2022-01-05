#pragma once

#include "graphbuilder.h"
#include "graphicsdata.h"
#include "mathsymbols.h"
#include "QeDos.h"

class QeGraph final :GraphBuilder
{
public:
    QeGraph(SettingsKeeper* settings, const QString& title, PlotParameters* plotParams, QFont font, QWidget* parent = nullptr);
	virtual void draw(QeDos* data, MathSymbols* symbols, const int currentGraphic, int angle );
    void drawData(QeDos* data, int angle, bool* isShowed);
};
