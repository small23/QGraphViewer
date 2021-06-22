#include "banddata.h"

BandData::BandData(): borders{}, fermi(0), type(0), nothing(0), interval(0)
{
}

QVector<int> BandData::countData(QList<QString> *content)
{
    int i=0;
    QVector<int> counter;
    counter.append(0);
    counter.append(0);
    counter.append(0);

    while (i<content->count())
    {
        if (content->at(i).contains("DOSS")){
            counter[2]++;
        }
        else if (content->at(i).contains("COHP")){
            counter[0]++;
        }
        else if (content->at(i).contains("COOP")){
            counter[1]++;
        }
        i++;
    }
    return counter;
}

void BandData::parseData(QList<QString> *content, const bool uhf)
{
	auto* indexListBand = new QVector<long>();
    auto* indexListDoss = new QVector<long>();
    auto* indexListCohp = new QVector<long>();
    auto* indexListCoop = new QVector<long>();
    auto* indexListMapn = new QVector<long>();

    clear();

    long i=0;
    while (i<content->count())
    {
        if (content->at(i).contains("BAND")){
            indexListBand->append(i);
        }
        else if (content->at(i).contains("DOSS")){
            indexListDoss->append(i);
        }
        else if (content->at(i).contains("COHP")){
            indexListCohp->append(i);
        }
        else if (content->at(i).contains("COOP")){
            indexListCoop->append(i);
        }
        else if (content->at(i).contains("MAPN")){
            indexListMapn->append(i);
        }
        i++;
    }

    if(indexListBand->count()>0)
        parseBandData(content, indexListBand);

    if(indexListCohp->count()>0)
        parseDccpData(content, indexListCohp, &outputCOHP, &oXCohp);
    if(indexListCoop->count()>0)
        parseDccpData(content, indexListCoop, &outputCOOP, &oXCoop);
    if(indexListMapn->count()>0)
        parseMapnData(content, indexListMapn, uhf);
    if (indexListDoss->count() > 0)
        parseDccpData(content, indexListDoss, &outputDOSS, &oXDoss);

    delete indexListBand;
    delete indexListDoss;
    delete indexListCohp;
    delete indexListCoop;
    delete indexListMapn;

}

void BandData::clear()
{
    outputBAND.clear();
    outputCOHP.clear();
    outputCOOP.clear();
    outputDOSS.clear();
    outputMAPN.clear();

    oXBand.clear();
    oXCohp.clear();
    oXCoop.clear();
    oXDoss.clear();
    oXMapn.clear();

    oYMapn.clear();
    oXTempMapn.clear();
    oYTempMapn.clear();
	
    kPoints.clear();
    type = -1;

    borders[0] = 999999;
    borders[1] = -999999;
}

void BandData::parseBandData(QList<QString> *content, QVector<long> *indexList0Band)
{
    QString c = content->at(indexList0Band->at(0));
    const long int countY=c.mid(9,4).toInt();
    for (int i=0; i<countY; i++)
    {
        QVector<double> a;
        outputBAND.append(a);
    }

    for (int i=0; i<indexList0Band->count(); i++)
    {
        c=content->at(indexList0Band->at(i));
        const long int  countX=c.mid(15,3).toInt();

        c.remove(0,18);
        QTextStream getBasicData(&c);
        getBasicData >>nothing  >> interval >> fermi;

        QVector<double> test;
        QString input;
        const long int strCount=ceil(static_cast<double>(countX * countY)/6); //ceil
        for (int j=0; j<strCount; j++)
        {
            input+=content->at(indexList0Band->at(i)+3+j);
        }

        QTextStream stream(&input);
        double tempN;
        while(!stream.atEnd())
        {
            stream>>tempN;
            test.append(tempN*27.21138602);
        }

        for (int j=0; j<countY; j++)
        {
            for(int jj=0; jj<countX; jj++)
            {
                outputBAND[j].append(test.at(jj*countY+j));
            }
        }

        for(int j=0; j<countX; j++)
        {
            if (oXBand.count()==0)
                oXBand.append(0);
            else
                oXBand.append(oXBand.at(oXBand.count()-1)+interval);
        }
        if (oXBand.count() - countX - 1>0)
			kPoints.append(oXBand.at(oXBand.count()-countX-1));
    }
    kPoints.append(oXBand.at(oXBand.count()-1));
    fermi=fermi*27.21138602;
}

void BandData::parseDccpData(QList<QString> *content, QVector<long> *indexList, QVector<QVector<double>> *output, QVector<double> *oX)
{
    long int countX=0;
    double startX;
    QString c = content->at(indexList->at(0));
    const long int countY=c.mid(9,4).toInt();
    c=content->at(indexList->at(0)+1);
    QTextStream getStartXData(&c);
    getStartXData >>nothing  >> startX;

    for (int i=0; i<indexList->count(); i++)
    {
        c=content->at(indexList->at(i));
        countX=c.mid(15,3).toInt();

        c.remove(0,18);
        QTextStream getBasicData(&c);
        getBasicData >>nothing  >> interval >> fermi;
        interval*=27.21138602;
        QVector<double> test;
        QString input;
        const long int strCount=ceil(static_cast<double>(countX * countY)/6);
        for (int j=0; j<strCount; j++)
        {
            input+=content->at(indexList->at(i)+3+j);
        }

        QTextStream stream(&input);
        double tempN;
        while(!stream.atEnd())
        {
            stream>>tempN;
            test.append(tempN);
        }

       output->append(test);
    }
    if (oX->count()==0)
    {
        for(int j=0; j<countX; j++)
        {
            if (oX->count()==0)
                oX->append(startX*27.21138602);
            else
                oX->append(oX->at(oX->count()-1)+interval);
            if (oX->at(oX->count() - 1) < borders[0])
                borders[0] = oX->at(oX->count() - 1);
            if (oX->at(oX->count() - 1) > borders[1])
                borders[1] = oX->at(oX->count() - 1);
        }
    }
    fermi=fermi*27.21138602;
}

void BandData::parseMapnData(QList<QString> *content, QVector<long> *indexList, const bool uhf)
{
    long int countX=0, countY=0;
    double intervX, intervY;
    QString c;
    QVector<QVector<double>> outputTemp;

    c=content->at(indexList->at(0));

    if (c.contains("-%-0MAPN"))
        type=0;
    else if (c.contains("-%-1MAPN"))
        type=1;
    else if (c.contains("-%-2MAPN"))
        type=2;
    else if (c.contains("-%-3MAPN"))
        type=3;

    c.remove(0,8);
    QTextStream getBasicData(&c);
    getBasicData >> countX >> countY >> intervX  >> intervY >> nothing;

    for (int i=0; i<indexList->count(); i++)
    {
        c=content->at(indexList->at(i));
        QVector<double> test;
        QString input;
        const long int strCount=ceil(static_cast<double>(countX * countY)/6);
        for (int j=0; j<strCount; j++)
        {
            input+=content->at(indexList->at(i)+3+j);
        }

        QTextStream stream(&input);
        double tempN;
        while(!stream.atEnd())
        {
            stream>>tempN;
            test.append(tempN);
        }
        outputTemp.append(test);
        QVector<double> b;
        outputMAPN.append(test); //b
    }

    /*
     * Если 1 или 3 - 2/4 файла (блока)
     * Если 0 и 2 - 2/1 файла (блока)
     * 0:2 - 1 без изменения, 2 это 1 блок - 2 блок
     * 1:3 - 2 файла без изменения из 1 и 2 блока, 4: 1 блок без изменения,
     * 2 файл без изменения, 3 файл: 1 блок - 3 блок, 4 файл: 2 блок - 4 блок
    */
    if (outputMAPN.count()==4 && (type==1 || type==3))
    {
        for (int i=0; i<outputMAPN[0].count(); i++)
        {
            outputMAPN[2][i]=outputMAPN[0][i]-outputMAPN[2][i];
            outputMAPN[3][i]=outputMAPN[1][i]-outputMAPN[3][i];
        }
    }
    else if (outputMAPN.count()==2 && (type==0 || type==2))
    {
    	if (!uhf)
    	{
			for (int i = 0; i < outputMAPN[0].count(); i++)
			{
				outputMAPN[1][i] = outputMAPN[0][i] - outputMAPN[1][i];
			}
    	}

    }

    for(int j=0; j<countX; j++)
    {
        if (oXTempMapn.count()==0)
            oXTempMapn.append(0);
        else
            oXTempMapn.append(oXTempMapn.at(oXTempMapn.count()-1)+intervX / 0.529177208 );
    }

    for(int j=0; j<countY; j++)
    {
        if (oYTempMapn.count()==0)
            oYTempMapn.append(0);
        else
            oYTempMapn.append(oYTempMapn.at(oYTempMapn.count()-1)+intervY / 0.529177208 );
    }

    for (int i=0; i<countY; i++)
    {
        for (int j=0; j<countX; j++)
        {
            oXMapn.append(oXTempMapn.at(j));
            oYMapn.append(oYTempMapn.at(i));
        }
    }
}

void BandData::rotateData(const int angle)
{
    QVector<QVector<double>> temp = outputMAPN;
    const QVector<double> tempX = oXTempMapn;
    const QVector<double> tempY = oYTempMapn;

    switch (angle)
    {
    case 0:
        break;
    case 90:
        for (int i=0; i<oXTempMapn.count(); i++)
        {
            for (int j=0; j<oYTempMapn.count(); j++)
            {
                for (int ii=0; ii<outputMAPN.count(); ii++)
                    outputMAPN[ii][i*oYTempMapn.count()+j]=temp[ii][(oYTempMapn.count()-j-1)*oXTempMapn.count()+i];
            }
        }
        oXTempMapn.clear();
        oYTempMapn.clear();
        oXTempMapn=tempY;
        oYTempMapn=tempX;
        oXMapn.clear();
        oYMapn.clear();
        for (int i=0; i<oYTempMapn.count(); i++)
        {
            for (int j=0; j<oXTempMapn.count(); j++)
            {
                oXMapn.append(oXTempMapn[j]);
                oYMapn.append(oYTempMapn[i]);
            }
        }
        break;
    case 180:
        for (int i = 0; i<outputMAPN[0].count(); i++)
        {
            for (int ii=0; ii<outputMAPN.count(); ii++)
                outputMAPN[ii][i]=temp[ii][outputMAPN[ii].count()-i-1];
        }
        break;
    case 270:
        for (int i=0; i<oXTempMapn.count(); i++)
        {
            for (int j=0; j<oYTempMapn.count(); j++)
            {
                for (int ii=0; ii<outputMAPN.count(); ii++)
                    outputMAPN[ii][i*oYTempMapn.count()+j]=temp[ii][(j+1)*oXTempMapn.count()-1-i];
            }
        }
        oXTempMapn.clear();
        oYTempMapn.clear();
        oXTempMapn=tempY;
        oYTempMapn=tempX;
        oXMapn.clear();
        oYMapn.clear();
        for (int i=0; i<oYTempMapn.count(); i++)
        {
            for (int j=0; j<oXTempMapn.count(); j++)
            {
                oXMapn.append(oXTempMapn[j]);
                oYMapn.append(oYTempMapn[i]);
            }
        }
        break;
    default: ;
    }
}
