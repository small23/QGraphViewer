#include "customtableview.h"

CustomTableView::CustomTableView(QWidget* parent)
	: QTableView(parent), tab5tableModel(new QStandardItemModel())
{
	tab5tableModel->setColumnCount(4);
	tab5tableModel->setRowCount(1);
	this->setModel(tab5tableModel);
	connect(this->model(), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), 
		this, SLOT(onDataChanged(const QModelIndex&, const QModelIndex&)));
	localValidator = new QRegExpValidator(QRegExp(R"(^[+\-]?(?:(?:0|[1-9]\d*)(?:\.\d*)?|\.\d+)(?:\d[eE][+\-]?\d+)?$)"));
}

CustomTableView::~CustomTableView()
{
}

void CustomTableView::onDataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight) const
{
	if (topLeft.row() + 1 == tab5tableModel->rowCount())
	{
		auto item = tab5tableModel->data(topLeft);
		QString data = item.toString();
		data.replace(" ", "");
		if (data != "")
		{
			QList<QStandardItem*> items;
			for (int column = 0; column < tab5tableModel->columnCount(); ++column)
			{
				QStandardItem* item = new QStandardItem();
				item->setText("");
				items.append(item);
			}
			tab5tableModel->insertRow(tab5tableModel->rowCount(), items);
		}
		else
		{
			QStandardItem* item = tab5tableModel->item(topLeft.row(), topLeft.column());
			if (item != nullptr)
			{
				item->setText("");
				return;
			}
		}
	}
	else
	{
		bool flagNotEmpty = false;
		for (int i = 0; i < tab5tableModel->columnCount(); i++)
		{
			QStandardItem* item = tab5tableModel->item(topLeft.row(), i);
			if (item != nullptr)
			{
				QString data = item->text();
				data.replace(" ", "");
				if (!data.isEmpty())
				{
					flagNotEmpty = true;
					break;
				}
			}
		}
		if (!flagNotEmpty)
		{
			tab5tableModel->removeRow(topLeft.row());
			return;
		}
	}

	QStandardItem* item = tab5tableModel->item(topLeft.row(), topLeft.column());
	if (item != nullptr)
	{
		if (topLeft.column() > 0)
		{
			QString textForValidation = item->text();
			if (textForValidation!="")
			{
				int index = 0;
				auto res = localValidator->validate(textForValidation, index);
				if (res == QValidator::State::Acceptable)
				{
					item->setBackground(QBrush(Qt::white));
				}
				else
					item->setBackground(QBrush(Qt::red));
			}
			else
				item->setBackground(QBrush(Qt::white));
		}
	}
}

void CustomTableView::keyPressEvent(QKeyEvent* event)
{
	if (event->type() == QKeyEvent::KeyPress) {
		if (event->matches(QKeySequence::Paste)) {
			const QClipboard* clipboard = QApplication::clipboard();
			const QMimeData* mimeData = clipboard->mimeData();
			QString data;

			if (mimeData->hasHtml()) {
				data = mimeData->html();
				data = data.remove(QRegExp("<[^>]*>"));
			}
			else if (mimeData->hasText()) {
				data = mimeData->text();
			}

			if (data != "")
			{
				QStringList dataRows = data.split(QRegExp("[\r\n]"), QString::SkipEmptyParts);
				QVector<QStringList> cells;
				for (int i=0; i<dataRows.count(); i++)
				{
					cells.append(dataRows[i].split(QRegExp("[ \t]"), QString::SkipEmptyParts));
				}
				auto sel = this->selectedIndexes();
				if (sel.count() > 0)
				{
					auto modelIndex = sel.at(0);
					
					int indexC = modelIndex.column();
					int indexR = modelIndex.row();
					int indexMatrixC = 0;
					int indexMatrixR = 0;
					while(true)
					{
						QStandardItem* item = new QStandardItem();
						item->setText(cells[indexMatrixR][indexMatrixC]);
						tab5tableModel->setItem(indexR, indexC, item);
						indexMatrixC++;
						indexC++;
						if (indexMatrixC >= cells[indexMatrixR].count())
						{
							indexMatrixC = 0;
							indexMatrixR++;
						}
						if (indexC >= tab5tableModel->columnCount())
						{
							indexC = 0;
							indexR++;
						}
						if (indexMatrixR >= cells.count())
							break;
					}
				}
			}
			else
				QTableView::keyPressEvent(event);
		}
		else if (event->matches(QKeySequence::Delete) || event->matches(QKeySequence::Backspace) || event->key() == Qt::Key_Backspace)
		{
			auto sel = this->selectedIndexes();
			for(int i= sel.size() - 1; i>=0; i--)
			{
				auto modelIndex = sel[i];
				QStandardItem* item = tab5tableModel->item(modelIndex.row(), modelIndex.column());
				if (item != nullptr)
				{
					item->setText("");
				}
			}
		}
		else {
			QTableView::keyPressEvent(event);
		}
	}
}
