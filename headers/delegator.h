#ifndef DELEGATOR_H
#define DELEGATOR_H

//Класс проверки валидности полей ввода чисел
#include <QObject>
#include <QWidget>
#include <QItemDelegate>
#include <QLineEdit>

class Delegator : public QItemDelegate
{
public:
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem & option, const QModelIndex & index) const override
    {
	    auto lineEdit = new QLineEdit(parent);
	    const auto localValidator = new QRegExpValidator(QRegExp(R"([+-]?\d*[\.]?\d+)"));
        lineEdit->setValidator(localValidator);
        return lineEdit;
    }
};

#endif // DELEGATOR_H
