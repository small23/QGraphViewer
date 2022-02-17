#include "qezonedata.h"

QeZoneData::QeZoneData()
{

}

void QeZoneData::parseData(QList<QString>* content)
{
    long int countX = 0, countY = 0;
    double temp;
    QString c;
    c = content->at(0);
    const QRegExp rx(QLatin1Literal("[^0-9]+"));
    const auto&& parts = c.split(rx, QString::SkipEmptyParts);
    if (parts.size()==2)
    {
        countY = parts.at(0).toLong();
        countX = parts.at(1).toLong();
        for (int i=0; i< countY; i++)
        {
            outputY.append(QVector<double>(0));
        }
    }
	QTextStream getData(&c);
    int i = 0;
    int inLineCounter = 0;
    while (i < countX)
    {
        double x = NAN, y = NAN, z = NAN;
        inLineCounter++;
        c = content->at(inLineCounter);
        getData.setString(&c);
        getData >> x >> y >> z;
        if (!(x == NAN || y == NAN || z == NAN) && getData.atEnd())
        {
            outputX.append(sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)));
            originVector.append(QVector<double>({ x, y, z }));
        }
           
        else
        {
            this->clear();
            return;
        }
        int counterY = 0;
        while(true)
        {
            if (inLineCounter < content->count())
            {
                inLineCounter++;
                c = content->at(inLineCounter);
                getData.setString(&c);
            }
            else
            {
                this->clear();
                return;
            }
            while (!getData.atEnd())
            {
                getData >> temp;
                outputY[counterY].append(temp);
                counterY++;
                if (!(counterY < countY))
                    break;
            }
            if (!(counterY < countY))
                break;
        }
        i++;
        
    }

    for (int i=outputX.count()-1; i>0; i--)
    {
        outputX[i] = abs(outputX[i] - outputX[i - 1]);
    }
    outputX[0] = 0;
    for (int i = 2; i < outputX.count(); i++)
    {
        outputX[i] = outputX[i] + outputX[i - 1];
    }
}

void QeZoneData::clear()
{
	outputX.clear();
	outputY.clear();
    originVector.clear();
}
