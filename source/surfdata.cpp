#include "surfdata.h"

SurfData::SurfData()
{


}

void SurfData::ParseData(QList<QString> *content)
{
    oX.clear();
    oY.clear();
    oRepeatX.clear();
    oRepeatY.clear();
    oF.clear();

    long int countX=0, countY=0;
    double xMin, yMin, stepX, stepY, nothing, temp;
    QString c;
    c=content->at(1);
    QTextStream getData(&c);
    getData >> countX >> countY;
    c=content->at(2);
    getData.setString(&c);
    getData >> xMin >> nothing >> stepX;
    c=content->at(3);
    getData.setString(&c);
    getData >> yMin >> nothing >> stepY;

    for (int i=5; i<content->count(); i++)
    {
        c=content->at(i);
        getData.setString(&c);
        while(!getData.atEnd())
        {
            getData>>temp;
            oF.append(temp);
        }
    }

    oX.append(xMin);
    oY.append(yMin);

    for (int i=1; i<countX; i++)
        oX.append(oX.at(i-1)+stepX);
    for (int i=1; i<countY; i++)
        oY.append(oY.at(i-1)+stepY);

    for (int i=0; i<countY; i++)
    {
        for (int j=0; j<countX; j++)
        {
            oRepeatX.append(oX.at(j));
            oRepeatY.append(oY.at(i));
        }
    }
}

void SurfData::clear()
{
    oX.clear();
    oY.clear();
    oRepeatX.clear();
    oRepeatY.clear();
    oF.clear();
}

void SurfData::RotateData(int angle)
{
    QVector<double> temp = oF;
    QVector<double> tempX = oX;
    QVector<double> tempY = oY;

    switch (angle)
    {
    case 0:
        break;
    case 90:
        for (int i=0; i<oX.count(); i++)
        {
            for (int j=0; j<oY.count(); j++)
            {
                oF[i*oY.count()+j]=(temp[(oY.count()-j-1)*oX.count()+i]);
            }
        }
        oX.clear();
        oY.clear();
        oX=tempY;
        oY=tempX;
        oRepeatX.clear();
        oRepeatY.clear();
        for (int i=0; i<oY.count(); i++)
        {
            for (int j=0; j<oX.count(); j++)
            {
                oRepeatX.append(oX.at(j));
                oRepeatY.append(oY.at(i));
            }
        }
        break;
    case 180:
        for (int i = 0; i<oF.count(); i++)
        {
            oF[i]=temp[oF.count()-i-1];
        }
        break;
    case 270:
        for (int i=0; i<oX.count(); i++)
        {
            for (int j=0; j<oY.count(); j++)
            {
                oF[i*oY.count()+j]=(temp[(j+1)*oX.count()-1-i]);
            }
        }
        oX.clear();
        oY.clear();
        oX=tempY;
        oY=tempX;
        oRepeatX.clear();
        oRepeatY.clear();
        for (int i=0; i<oY.count(); i++)
        {
            for (int j=0; j<oX.count(); j++)
            {
                oRepeatX.append(oX.at(j));
                oRepeatY.append(oY.at(i));
            }
        }
        break;
    default:
        return;
    }
}
