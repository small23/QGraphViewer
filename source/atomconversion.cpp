// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "atomconversion.h"

AtomConversion::AtomConversion(Ui::MainWindow* uiExt, SettingsKeeper* settings, QWidget* parent) : QWidget(parent)
{
	ui = uiExt;
	this->settings = settings;
}

void AtomConversion::convertAtoms()
{
	QVector<QVector<double>> res = convert();

	if (res.isEmpty())
	{
		QMessageBox::critical(this, STR_ErrorTitle_ParsingError, STR_ErrorMessage_NoDataForSave);
		return;
	}
	const QString fileName = QFileDialog::getSaveFileName(nullptr,
		STR_Dialog_SaveFile, settings->getLastPath() + "Atoms.txt",
	                                                      "Text file (*.txt);;All Files (*)");
	if (fileName != "")
	{
		const QFileInfo fileInfo(fileName);
		settings->updatePath(fileInfo.absolutePath());
		QFile file(fileName);
		if (file.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			QTextStream stream(&file);

			for (int i = 0; i < res.count(); i++)
			{
				QString output = QString::number(res[i][0], 'g', 8) + " " + QString::number(res[i][1], 'g', 8) + " " +
					QString::number(res[i][2], 'g', 8) + "\n";
				stream << output;
			}

			file.close();
		}
	}
}

QVector<QVector<double>> AtomConversion::convert() const
{
	Eigen::MatrixXd atomsRotationMatrix(3, 3);
	Eigen::MatrixXd atomTemp(3, 1);
	QVector<QVector<double>> res;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			atomsRotationMatrix(i, j) = ui->tab3RotationTable->item(i, j)->text().toDouble();
		}
	}
	const QString str = ui->tab3TextEditAtoms->toPlainText();
	const QStringList b = str.split("\n");
	for (int i = 0; i < b.count(); i++)
	{
		QStringList c = b.at(i).split(" ");
		c.removeAll("");
		if (c.count() == 3)
		{
			atomTemp(0, 0) = c.at(0).toDouble();
			atomTemp(1, 0) = c.at(1).toDouble();
			atomTemp(2, 0) = c.at(2).toDouble();
			atomTemp = atomsRotationMatrix.inverse() * atomTemp;
			res.append({atomTemp(0, 0), atomTemp(1, 0), atomTemp(2, 0)});
		}
	}
	return res;
}

void AtomConversion::convertAndSearchAtoms()
{
	Eigen::MatrixXd atomsRotationMatrix(3, 3);
	Eigen::MatrixXd atomTemp(3, 1);
	QVector<QVector<double>> res; //= convert();;
	QVector<QVector<double>> resElem;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			atomsRotationMatrix(i, j) = ui->tab3RotationTable->item(i, j)->text().toDouble();
		}
	}
	QString str = ui->tab3TextEditAtoms->toPlainText();
	QStringList b = str.split("\n");
	for (int i = 0; i < b.count(); i++)
	{
		QStringList c = b.at(i).split(" ");
		c.removeAll("");
		if (c.count() == 3)
		{
			atomTemp(0, 0) = c.at(0).toDouble();
			atomTemp(1, 0) = c.at(1).toDouble();
			atomTemp(2, 0) = c.at(2).toDouble();
			if (ui->tab3RadioButtonAtomsSet1->isChecked() == false)
				atomTemp = atomsRotationMatrix.inverse() * atomTemp;
			res.append({atomTemp(0, 0), atomTemp(1, 0), atomTemp(2, 0)});
		}
	}

	str = ui->tab3TextEditAtomsElem->toPlainText();
	b.clear();
	b = str.split("\n");
	for (int i = 0; i < b.count(); i++)
	{
		QStringList c = b.at(i).split(" ");
		c.removeAll("");
		if (c.count() == 3)
			resElem.append({c.at(0).toDouble(), c.at(1).toDouble(), c.at(2).toDouble()});
	}

	double n1 = 0, n2 = 0, n3 = 0;

	ui->tab3ConvertedAtomsTable->clear();
	ui->tab3ConvertedAtomsTable->setRowCount(0);

	for (int i = 0; i < res.count(); i++)
	{
		long int flag = -1;
		for (int j = 0; j < resElem.count(); j++)
		{
			if (ui->tab3RadioButtonAtomsSet1->isChecked() == false)
			{
				n1 = res[i][0] - resElem[j][0];
				n2 = res[i][1] - resElem[j][1];
				n3 = res[i][2] - resElem[j][2];
			}
			else
			{
				Eigen::MatrixXd matrixXd(3, 1);
				matrixXd(0, 0) = res[i][0] - resElem[j][0];
				matrixXd(1, 0) = res[i][1] - resElem[j][1];
				matrixXd(2, 0) = res[i][2] - resElem[j][2];
				matrixXd = atomsRotationMatrix.inverse() * matrixXd;
				n1 = matrixXd(0, 0);
				n2 = matrixXd(1, 0);
				n3 = matrixXd(2, 0);
			}
			if (fabs(round(n1) - n1) < 0.001 && fabs(round(n2) - n2) < 0.001 && fabs(round(n3) - n3) < 0.001)
			{
				flag = j;
				break;
			}
		}
		if (flag > -1)
		{
			ui->tab3ConvertedAtomsTable->setRowCount(ui->tab3ConvertedAtomsTable->rowCount() + 1);
			QTableWidgetItem* itm = new QTableWidgetItem(QString::number(i + 1));
			ui->tab3ConvertedAtomsTable->setItem(ui->tab3ConvertedAtomsTable->rowCount() - 1, 0, itm);
			itm = new QTableWidgetItem(QString::number(flag + 1));
			ui->tab3ConvertedAtomsTable->setItem(ui->tab3ConvertedAtomsTable->rowCount() - 1, 1, itm);
			itm = new QTableWidgetItem(QString::number(round(n1)));
			ui->tab3ConvertedAtomsTable->setItem(ui->tab3ConvertedAtomsTable->rowCount() - 1, 2, itm);
			itm = new QTableWidgetItem(QString::number(round(n2)));
			ui->tab3ConvertedAtomsTable->setItem(ui->tab3ConvertedAtomsTable->rowCount() - 1, 3, itm);
			itm = new QTableWidgetItem(QString::number(round(n3)));
			ui->tab3ConvertedAtomsTable->setItem(ui->tab3ConvertedAtomsTable->rowCount() - 1, 4, itm);
		}
	}
	ui->tab3ConvertedAtomsTable->setHorizontalHeaderLabels(QStringList() << STR_XLSX_Short_SourceAtomNumber << STR_XLSX_Short_AtomNumber
		<< STR_XLSX_Extended_N1 << STR_XLSX_Extended_N2 << STR_XLSX_Extended_N3);
	if (ui->tab3ConvertedAtomsTable->rowCount() > 0)
	{
		const QString fileName = QFileDialog::getSaveFileName(nullptr,
			STR_Dialog_SaveFile, settings->getLastPath() + "Atoms.xlsx",
		                                                      "Excel file (*.xlsx);;All Files (*)");
		if (fileName != "")
		{
			const QFileInfo fileinfo(fileName);
			settings->updatePath(fileinfo.absolutePath());
			QXlsx::Document xlsx;
			xlsx.write(1, 1, STR_XLSX_Extended_SourceAtomNumber);
			xlsx.write(1, 2, STR_XLSX_Extended_AtomNumber);
			xlsx.write(1, 3, STR_XLSX_Extended_N1);
			xlsx.write(1, 4, STR_XLSX_Extended_N2);
			xlsx.write(1, 5, STR_XLSX_Extended_N3);
			for (int j = 0; j < ui->tab3ConvertedAtomsTable->rowCount(); j++)
			{
				xlsx.write(j + 2, 1, ui->tab3ConvertedAtomsTable->item(j, 0)->text().toDouble());
				xlsx.write(j + 2, 2, ui->tab3ConvertedAtomsTable->item(j, 1)->text().toDouble());
				xlsx.write(j + 2, 3, ui->tab3ConvertedAtomsTable->item(j, 2)->text().toDouble());
				xlsx.write(j + 2, 4, ui->tab3ConvertedAtomsTable->item(j, 3)->text().toDouble());
				xlsx.write(j + 2, 5, ui->tab3ConvertedAtomsTable->item(j, 4)->text().toDouble());
			}
			xlsx.setColumnWidth(1, 20);
			xlsx.setColumnWidth(2, 18);
			xlsx.setColumnWidth(3, 5);
			xlsx.setColumnWidth(4, 5);
			xlsx.setColumnWidth(5, 5);
			QApplication::processEvents();
			const bool success = xlsx.saveAs(fileName); // save the document as 'Test.xlsx'
			if (success != true)
			{
				QMessageBox::critical(this, STR_ErrorTitle_SaveError,
					STR_ErrorMessage_CantOpenFileForWrite.arg(fileName));
				return;
			}
			QMessageBox::information(this, STR_MessageBoxTitle_DataProcessed, STR_MessageBoxMessage_DataProcessedAndSaved);
		}
	}
	else
		QMessageBox::warning(this, STR_ErrorTitle_ProcessingError,
			STR_ErrorMessage_NoAtomsError);
}
