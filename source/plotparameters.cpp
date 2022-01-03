// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "plotparameters.h"

PlotParameters::PlotParameters(Ui::MainWindow* uiInt, QWidget* parentInt)
{
	ui = uiInt;
	parent = parentInt;
	for (int i = 0; i < 6; i++)
	{
		tab1PlotParams[i].color = QColor(0, 0, 0);
		tab1PlotParams[i].width = 1;
		tab1PlotParams[i].style = Qt::PenStyle::SolidLine;
	}
	UniversalLineParams test;
	test.color = QColor(0, 0, 0);
	test.width = 2;
	test.style = Qt::PenStyle::SolidLine;
	test.styleId = 0;
	test.show = false;
	test.multiplier = 1;
	tab2PlotParams = new QVector<UniversalLineParams>();
	tab2PlotParams->append(test);
	tab2ShowOx = false;
	tab2FxInverse = false;
	tab1surfaceDivider = 0;
	tab1surfacePrecision = 0;
	tab1surfaceWidth = 0;
	tab2zeroShift = false;
	commonUhf = false;
	colorContours = false;
	drawRes = 0;
	tab2FermiLevelWidth = 0;
	tab2ShowFermiLine = false;
	tab2OyTicks = false;
	tab2OxTicks = false;

	UniversalLineParams test2;
	test2 = test;
	tab5FermiLevelColor = QColor(0, 0, 0);;
	tab5PlotParams = new QVector<UniversalLineParams>();
	tab5PlotParams->append(test2);
	tab5FermiLevelWidth = 0;
	tab5ShowFermiLine = false;
	tab5OyTicks = false;
	tab5OxTicks = false;

	tab5LinesCounter = new QVector<int>();
}

void PlotParameters::updatePlotParams(const int tabId)
{
	if (tabId == 1)
	{
		bool succsess;
		tab1surfaceWidth = ui->tab1SpinnerBoxContourWidth->value();
		tab1surfaceDivider = ui->tab1SpinnerBoxLevelDivider->value();
		tab1surfacePrecision = ui->tab1LineEditLevelPrecision->text().toDouble(&succsess);
		if (!succsess)
		{
			ui->tab1LineEditLevelPrecision->setText("0.001");
			tab1surfacePrecision = 0.001;
		}
		else
		{
			if (tab1surfacePrecision < 0.000001)
			{
				ui->tab1LineEditLevelPrecision->setText("0.000001");
				tab1surfacePrecision = 0.000001;
			}
		}

		tab1PlotParams[0].width = ui->tab1LineWidth1->value();
		tab1PlotParams[1].width = ui->tab1LineWidth2->value();
		tab1PlotParams[2].width = ui->tab1LineWidth3->value();
		tab1PlotParams[3].width = ui->tab1LineWidth4->value();
		tab1PlotParams[4].width = ui->tab1LineWidth5->value();
		tab1PlotParams[5].width = ui->tab1LineWidth6->value();

		tab1PlotParams[0].show = ui->tab1CheckBoxShow1->isChecked();
		tab1PlotParams[1].show = ui->tab1CheckBoxShow2->isChecked();
		tab1PlotParams[2].show = ui->tab1CheckBoxShow3->isChecked();
		tab1PlotParams[3].show = ui->tab1CheckBoxShow4->isChecked();
		tab1PlotParams[4].show = ui->tab1CheckBoxShow5->isChecked();
		tab1PlotParams[5].show = ui->tab1CheckBoxShow6->isChecked();
		tab1PlotParams[6].show = ui->tab1CheckBoxShow7->isChecked();

		colorContours = ui->tab1CheckBoxColorLevels->isChecked();

		for (int i = 0; i < 4; i++)
		{
			QString name = QString("tab1LineType%1").arg(i + 1);
			QComboBox* box = parent->findChild<QComboBox*>(name);
			if (box != nullptr)
			{
				switch (box->currentIndex()) {
				case 0:
					tab1PlotParams[i].style = Qt::PenStyle::SolidLine;
					break;
				case 1:
					tab1PlotParams[i].style = Qt::PenStyle::DashLine;
					break;
				case 2:
					tab1PlotParams[i].style = Qt::PenStyle::DotLine;
					break;
				case 3:
					tab1PlotParams[i].style = Qt::PenStyle::DashDotLine;
					break;
				default:
					break;
				}
			}
		}
		for (int i = 4; i < 6; i++)
		{
			QString name = QString("tab1LineType%1").arg(i + 1);
			QComboBox* box = parent->findChild<QComboBox*>(name);
			if (box != nullptr)
			{
				switch (box->currentIndex()) {
				case 0:
					tab1PlotParams[i].pointStyle = QCPScatterStyle::ssCircle;
					break;
				case 1:
					tab1PlotParams[i].pointStyle = QCPScatterStyle::ssPlus;
					break;
				case 2:
					tab1PlotParams[i].pointStyle = QCPScatterStyle::ssStar;
					break;
				case 3:
					tab1PlotParams[i].pointStyle = QCPScatterStyle::ssDisc;
					break;
				case 4:
					tab1PlotParams[i].pointStyle = QCPScatterStyle::ssCross;
					break;
				case 5:
					tab1PlotParams[i].pointStyle = QCPScatterStyle::ssSquare;
					break;
				case 6:
					tab1PlotParams[i].pointStyle = QCPScatterStyle::ssDiamond;
					break;
				case 7:
					tab1PlotParams[i].pointStyle = QCPScatterStyle::ssTriangle;
					break;
				case 8:
					tab1PlotParams[i].pointStyle = QCPScatterStyle::ssTriangleInverted;
					break;
				default:
					break;
				}
			}
		}
	}
	else if (tabId == 2)
	{
		const int workingLine = ui->tab2ComboBoxLineSelector->currentIndex();
		tab2PlotParams->data()[workingLine].width = ui->tab2SpinnerLineWidth->value();
		switch (ui->tab2ComboBoxLineType->currentIndex()) {
		case 0:
			tab2PlotParams->data()[workingLine].style = Qt::PenStyle::SolidLine;
			tab2PlotParams->data()[workingLine].styleId = 0;
			break;
		case 1:
			tab2PlotParams->data()[workingLine].style = Qt::PenStyle::DashLine;
			tab2PlotParams->data()[workingLine].styleId = 1;
			break;
		case 2:
			tab2PlotParams->data()[workingLine].style = Qt::PenStyle::DotLine;
			tab2PlotParams->data()[workingLine].styleId = 2;
			break;
		case 3:
			tab2PlotParams->data()[workingLine].style = Qt::PenStyle::DashDotLine;
			tab2PlotParams->data()[workingLine].styleId = 3;
			break;
		default:
			break;
		}
		tab2PlotParams->data()[workingLine].show = ui->tab2CheckBoxShow1->isChecked();
		tab2PlotParams->data()[workingLine].multiplier = ui->tab2SpinnerLineMultiplier->value();
		tab2FermiLevelWidth = ui->tab2SpinnerBoxFermiLevelWidth->value();
		tab2ShowFermiLine = ui->tab2CheckBoxFermiLevel->isChecked();
		tab2OxName = ui->tab2EditLineOxName->text();
		tab2OyName = ui->tab2EditLineOyName->text();
		tab2PlotName = ui->tab2EditLinePlotName->text();
		//tab2ShowOx=ui->tab2CheckBoxShowOx->isChecked();
		tab2OxTicks = ui->tab2CheckBoxShowOxTicks->isChecked();
		tab2OyTicks = ui->tab2CheckBoxShowOyTicks->isChecked();
		tab2FxInverse = ui->tab2CheckBoxFxSet->isChecked();
	}
	else if (tabId == 5)
	{
		int workingLine = ui->tab5ComboBoxLineSelector->currentIndex();
		for (int i = 0; i < ui->tab5LoadFilecomboBox->currentIndex(); i++)
			workingLine += this->tab5LinesCounter->at(i);
		tab5PlotParams->data()[workingLine].width = ui->tab5SpinnerLineWidth->value();
		tab5PlotParams->data()[workingLine].show = ui->tab5CheckBoxShow1->isChecked();
		tab5PlotParams->data()[workingLine].multiplier = ui->tab5SpinnerLineMultiplier->value();
		switch (ui->tab5ComboBoxLineType->currentIndex()) {
		case 0:
			tab5PlotParams->data()[workingLine].style = Qt::PenStyle::SolidLine;
			tab5PlotParams->data()[workingLine].styleId = 0;
			break;
		case 1:
			tab5PlotParams->data()[workingLine].style = Qt::PenStyle::DashLine;
			tab5PlotParams->data()[workingLine].styleId = 1;
			break;
		case 2:
			tab5PlotParams->data()[workingLine].style = Qt::PenStyle::DotLine;
			tab5PlotParams->data()[workingLine].styleId = 2;
			break;
		case 3:
			tab5PlotParams->data()[workingLine].style = Qt::PenStyle::DashDotLine;
			tab5PlotParams->data()[workingLine].styleId = 3;
			break;
		default:
			break;
		}
		tab5FermiLevelWidth = ui->tab5SpinnerBoxFermiLevelWidth->value();
		tab5ShowFermiLine = ui->tab5CheckBoxFermiLevel->isChecked();
		tab5FermiLevel = ui->tab5DOSFerm->text().toDouble();
		tab5PlotName = ui->tab5EditLinePlotName->text();
		tab5OyName = ui->tab5EditLineOxName->text();
		tab5OxName = ui->tab5EditLineOyName->text();
		tab5OyTicks = ui->tab5CheckBoxShowOyTicks->isChecked();
		tab5OxTicks = ui->tab5CheckBoxShowOxTicks->isChecked();
		tab5xMin = ui->tab5DOSXMin->text().toDouble();
		tab5xMax = ui->tab5DOSXMax->text().toDouble();
		tab5yMin = ui->tab5DOSYMin->text().toDouble();
		tab5yMax = ui->tab5DOSYMax->text().toDouble();
		tab5yMinZs = ui->tab5ZoneStructYMin->text().toDouble();
		tab5yMaxZs = ui->tab5ZoneStructYMax->text().toDouble();
	}

	tab2zeroShift = ui->tab2ZeroShift->isChecked();
	commonUhf = ui->tab2UHF->isChecked();

}

void PlotParameters::updateColors(const int colorId, const QColor& color)
{
	if (colorId < 7)
		tab1PlotParams[colorId - 1].color = color;
	else if (colorId == 8)
	{
		const int workingLine = ui->tab2ComboBoxLineSelector->currentIndex();
		tab2PlotParams->data()[workingLine].color = color;
	}
	else if (colorId == 7)
		tab2FermiLevel = color;
	else if (colorId == 9)
	{
		int workingLine = ui->tab5ComboBoxLineSelector->currentIndex();
		for (int i = 0; i < ui->tab5LoadFilecomboBox->currentIndex(); i++)
			workingLine += this->tab5LinesCounter->at(i);
		tab5PlotParams->data()[workingLine].color = color;
	}
	else if (colorId == 10)
		tab5FermiLevelColor = color;
}

void PlotParameters::tab2SetCountOfLines(int size) const
{
	UniversalLineParams temp;
	temp.color = tab2PlotParams->at(0).color;
	temp.show = tab2PlotParams->at(0).show;
	temp.style = tab2PlotParams->at(0).style;
	temp.width = tab2PlotParams->at(0).width;
	temp.styleId = tab2PlotParams->at(0).styleId;
	temp.multiplier = tab2PlotParams->at(0).multiplier;
	tab2PlotParams->clear();
	tab2PlotParams->append(temp);
	for (int i = 1; i < size; i++)
	{
		UniversalLineParams temp2;
		temp2.color = QColor(0, 0, 0);
		temp2.width = 2;
		temp2.style = Qt::PenStyle::SolidLine;
		temp2.styleId = 0;
		temp2.show = false;
		temp2.multiplier = 1;
		tab2PlotParams->append(temp2);
	}
}

void PlotParameters::tab5SetCountOfLines(int size) const
{
	UniversalLineParams temp;
	temp.color = tab5PlotParams->at(0).color;
	temp.show = tab5PlotParams->at(0).show;
	temp.style = tab5PlotParams->at(0).style;
	temp.width = tab5PlotParams->at(0).width;
	temp.styleId = tab5PlotParams->at(0).styleId;
	temp.multiplier = tab5PlotParams->at(0).multiplier;
	tab5PlotParams->clear();
	tab5PlotParams->append(temp);
	for (int i = 1; i < size; i++)
	{
		UniversalLineParams temp2;
		temp2.color = QColor(0, 0, 0);
		temp2.width = 2;
		temp2.style = Qt::PenStyle::SolidLine;
		temp2.styleId = 0;
		temp2.show = false;
		temp2.multiplier = 1;
		tab5PlotParams->append(temp2);
	}
}
