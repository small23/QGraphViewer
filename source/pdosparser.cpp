#include "headers/pdosparser.h"

PdosParser::PdosParser(QWidget *parent) : QWidget(parent)
{

}

QVector<QVector<AtomTypes>> PdosParser::getAtomData(QList<QString> *content) const
{
    QList<QString> c;
    QString b;
    long int lastNumber=1;
    long int dataBegin=-1;
    long int dataEnd=-1;
    bool convertsionPass;
    QVector<long int> cellsAtomsLocation;
    QVector<AtomTypes> atoms;
    QVector<QVector<AtomTypes>> atomsContainer;
    //int i=0;
    for(int i=0; i<content->count(); i++)
    {
        if (content->at(i).contains("LOCAL ATOMIC FUNCTIONS BASIS SET"))
            dataBegin=i;
        if (dataBegin!=-1)
        {
            if (content->at(i).contains("INF") && content->at(i).contains("***") )
            {
                dataEnd=i;
                break;
            }
        }
    }

    if ( dataBegin==-1) return atomsContainer;
    dataBegin+=4;
    cellsAtomsLocation.append(dataBegin);
    dataBegin+=1;
    for (int i=dataBegin; i<dataEnd; i++)
    {
        b=content->at(i).mid(0,4);
        b.toDouble(&convertsionPass);
        if (convertsionPass==true)
        {
            cellsAtomsLocation.append(i-1);
            cellsAtomsLocation.append(i);
        }
    }
    cellsAtomsLocation.append(dataEnd-1);
    if (cellsAtomsLocation.count()%2!=0) return atomsContainer;
    for (int ii=0; ii<cellsAtomsLocation.count(); ii+=2)
    {
        if (cellsAtomsLocation.at(ii)!=cellsAtomsLocation.at(ii+1))
        {
            atoms.clear();
            AtomTypes data;
            b=content->at(cellsAtomsLocation.at(ii));
            data.number=b.mid(0,4).toInt();
            data.name=b.mid(4,3);
            b=content->at(cellsAtomsLocation.at(ii)+1);
            data.begin=lastNumber;
            data.type=b.mid(36,2);
            for (int i=cellsAtomsLocation.at(ii)+1; i<cellsAtomsLocation.at(ii+1); i++)
            {
                b=content->at(i);
                if (QString::compare(b.mid(36,2),data.type)==0)
                {
                    data.end=b.mid(31,4).toInt();
                    lastNumber=data.end+1;
                }
                else if (QString::compare(b.mid(36,2),"  ")!=0)
                {
                    atoms.append(data);
                    data.begin=atoms.at(atoms.count()-1).end+1;
                    data.type=b.mid(36,2);
                    data.end=b.mid(31,4).toInt();
                    if (data.end==0) return atomsContainer;
                    data.name=atoms.at(atoms.count()-1).name;
                    data.number=atoms.at(atoms.count()-1).number;
                }
            }
            atoms.append(data);
        }
        else
        {
	        const long int delta=atoms.at(atoms.count()-1).end-atoms.at(0).begin+1;
            b=content->at(cellsAtomsLocation.at(ii));
            atoms.data()[0].number=b.mid(0,4).toInt();
            atoms.data()[0].name=b.mid(4,3);
            atoms.data()[0].begin+=delta;
            atoms.data()[0].end+=delta;
            for (int i=1; i<atoms.count(); i++)
            {
                atoms.data()[i].begin+=delta;
                atoms.data()[i].end+=delta;
                atoms.data()[i].number=atoms.at(0).number;
                lastNumber=atoms.at(i).end+1;
            }
        }
        atomsContainer.append(atoms);
    }

    if(atomsContainer.count()<=0)
    {
        return atomsContainer;
    }

    return atomsContainer;
}
