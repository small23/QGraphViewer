#pragma once
#include <QVector>
#include <QList>
#include <QTextStream>

class QeSurfData 
{


public:
	QeSurfData();
    QVector<double> oX, oY, oRepeatX, oRepeatY, oF;
    //QVector<QVector<double>> oF;
    //������ ������
    void parseData(QList<QString>* content);
	//������� ������ �� ���� 0-270 ��������
    void rotateData(int angle);
    void clear();
};
