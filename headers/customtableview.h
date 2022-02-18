#pragma once

#include <QTableWidget>
#include <QKeyEvent>
#include <QDebug>
#include <QApplication>
#include <QClipboard>
#include <QMimeData>
#include <qstandarditemmodel.h>

class CustomTableView : public QTableView
{
	Q_OBJECT
public:
	CustomTableView(QWidget *parent);
	~CustomTableView();

public slots:
	void onDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight) const;

private:
	void keyPressEvent(QKeyEvent* event) override;
	QStandardItemModel* tab5tableModel;
	QRegExpValidator* localValidator;
};
