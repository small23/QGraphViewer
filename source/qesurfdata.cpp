#include "qesurfdata.h"

QeSurfData::QeSurfData()
{

}

void QeSurfData::parseData(QList<QString>* content)
{
    oX.clear();
    oY.clear();
    oRepeatX.clear();
    oRepeatY.clear();
    oF.clear();

    long int countX = 0, countY = 0;
    double xMin, yMin, stepX, stepY, nothing, temp;
    QString c;
    c = content->at(0);
    QTextStream getData(&c);
    getData >> countX >> countY;
    countX += 1;
    countY += 1;
    int i = 0;
    int inLineCounter = 0;
    bool flagDone = false;
    while (i < countX)
    {
        inLineCounter++;
        c = content->at(inLineCounter);
        getData.setString(&c);
        while (!getData.atEnd())
        {
            getData >> temp;
            oX.append(temp);
            i++;
            if (!(i < countX))
                break;
        }
    }
    i = 0;
    flagDone = false;
    while (i < countY)
    {
        while (!getData.atEnd())
        {
            getData >> temp;
            oY.append(temp);
            i++;
            if (!(i < countX))
            {
                flagDone = true;
                break;
            }
               
        }
        if (!flagDone)
        {
            inLineCounter++;
            c = content->at(inLineCounter);
            getData.setString(&c);
        }
        
    }
    i = 0;
    flagDone = false;
    while (i < countY * countX)
    {
        while (!getData.atEnd())
        {
            getData >> temp;
            oF.append(temp);
            i++;
            if (!(i < countY * countX))
            {
                flagDone = true;
                break;
            }
        }
        if (!flagDone)
        {
            inLineCounter++;
            if (inLineCounter>=content->count())
            {
                this->clear();
                return;
            }
            c = content->at(inLineCounter);
            getData.setString(&c);
        }
    }

    for (int i = 0; i < countY; i++)
    {
        for (int j = 0; j < countX; j++)
        {
            oRepeatX.append(oX.at(j));
            oRepeatY.append(oY.at(i));
        }
    }
}


void QeSurfData::rotateData(const int angle)
{
    QVector<double> temp = oF;
    const QVector<double> tempX = oX;
    const QVector<double> tempY = oY;

    switch (angle)
    {
    case 0:
        break;
    case 90:
        for (int i = 0; i < oX.count(); i++)
        {
            for (int j = 0; j < oY.count(); j++)
            {
                oF[i * oY.count() + j] = temp[(oY.count() - j - 1) * oX.count() + i];
            }
        }
        oX.clear();
        oY.clear();
        oX = tempY;
        oY = tempX;
        oRepeatX.clear();
        oRepeatY.clear();
        for (int i = 0; i < oY.count(); i++)
        {
            for (int j = 0; j < oX.count(); j++)
            {
                oRepeatX.append(oX.at(j));
                oRepeatY.append(oY.at(i));
            }
        }
        break;
    case 180:
        for (int i = 0; i < oF.count(); i++)
        {
            oF[i] = temp[oF.count() - i - 1];
        }
        break;
    case 270:
        for (int i = 0; i < oX.count(); i++)
        {
            for (int j = 0; j < oY.count(); j++)
            {
                oF[i * oY.count() + j] = temp[(j + 1) * oX.count() - 1 - i];
            }
        }
        oX.clear();
        oY.clear();
        oX = tempY;
        oY = tempX;
        oRepeatX.clear();
        oRepeatY.clear();
        for (int i = 0; i < oY.count(); i++)
        {
            for (int j = 0; j < oX.count(); j++)
            {
                oRepeatX.append(oX.at(j));
                oRepeatY.append(oY.at(i));
            }
        }
        break;
    default:;
    }
}

void QeSurfData::clear()
{
    oX.clear();
    oY.clear();
    oRepeatX.clear();
    oRepeatY.clear();
    oF.clear();
}


