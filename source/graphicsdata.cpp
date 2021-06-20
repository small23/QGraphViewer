#include "graphicsdata.h"

int GraphicsData::GetAndParseMainData(QList<QString> fileFields, double cutOff)
{

    MolgraphConn->clear();
    MolgraphBass1->clear();
    MolgraphBass2->clear();
    MolgraphPoints->clear();
    Trajgrad->clear();
    Atoms->clear();
    content->clear();
    bool success;
    parsedFrameLoc=false;
    if (fileFields[3]!="")
    {
        ReadFileFromFS(fileFields[3],content);
        success=GetOffsetAndTransMatrix();
        if (!success)
            return 0;
        for (int i=0; i<fileFields.size(); i++)
        {
            if (fileFields[i]!="" && i!=4)
            {
                content->clear();
                ReadFileFromFS(fileFields[i],content);
                switch (i) {
                case 0:
                    success=GetTrajgradMolgraphData(false);
                    if (!success)
                        return -1;
                    break;
                case 1:
                    success=GetTrajgradMolgraphData(true);
                    if (!success)
                        return -2;
                    break;
                case 2:
                    success=GetAtomsData(cutOff);
                    if (!success)
                        return -3;
                    break;
                default:
                    break;
                }
            }
        }
    }
    return 1;
}

void GraphicsData::clear()
{
    MolgraphConn->clear();
    MolgraphBass1->clear();
    MolgraphBass2->clear();
    MolgraphPoints->clear();
    Trajgrad->clear();
    Atoms->clear();
    content->clear();
    parsedFrameLoc=false;
}

bool GraphicsData::GetOffsetAndTransMatrix()
{
    int counter=0;
    int matrixLine=-1;
    int offsetLine=-1;
    int inMatrixPos;
    double tempD;
    bool convertsionPass;
    QList<QString> c;
    QRegExp separator("( |,|:)");

    while (counter<content->count())
    {
        if (content->at(counter).contains("ROTAT. MATRIX")){
            matrixLine=counter;
            break;
        }
        counter++;
    }
    counter=0;
    while (counter<content->count())
    {
        if (content->at(counter).contains("ORIGIN AT")){
            offsetLine=counter;
            break;
        }
        counter++;
    }

    if (matrixLine==-1)
    {
        return 0;
    }
    if (offsetLine==-1)
    {
        return 0;
    }
    for (int i=matrixLine; i<matrixLine+3; i++)
    {
        inMatrixPos=0;
        c = content->at(i).split(separator);
        for (int j=0; j<c.count(); j++)
        {
            if (c.at(j)!="")
            {
                tempD=c.at(j).toDouble(&convertsionPass);
                if (convertsionPass==true)
                {
                    rotationMatrix(i-matrixLine,inMatrixPos)=tempD;
                    inMatrixPos++;
                }
            }
        }
    }

    inMatrixPos=0;
    c=content->at(offsetLine).split(separator);
    for (int j=0; j<c.count(); j++)
    {

        if (c.at(j)!="")
        {
            tempD=c.at(j).toDouble(&convertsionPass);
            if (convertsionPass==true)
            {
                offsetMatrix(0,inMatrixPos)=tempD;
                inMatrixPos++;
            }
        }
    }

    for (int i=0; i<2; i++)
    {
        inMatrixPos=0;
        c = content->at(matrixLine + 7 + i).split(separator);
        for (int j=0; j<c.count(); j++)
        {
            if (c.at(j)!="")
            {
                tempD=c.at(j).toDouble(&convertsionPass);
                if (convertsionPass==true)
                {
                    offsetGraph(i,inMatrixPos)=c.at(j).toDouble();
                    inMatrixPos++;
                }
            }
        }
    }
    frameLoc[0]=offsetGraph(0,0)/0.529177208;
    frameLoc[1]=offsetGraph(0,1)/0.529177208;
    frameLoc[2]=offsetGraph(1,0)/0.529177208;
    frameLoc[3]=offsetGraph(1,1)/0.529177208;
    parsedFrameLoc=true;
    return 1;
}

bool GraphicsData::GetTrajgradMolgraphData(bool mode)
{
	long int posInList=0;
    UniversalLines line;// = new UniversalLines();
    UniversalPoints point;// = new UniversalPoints();
    MatrixXd temp(3,1);

    while(posInList<content->count())
    {
        line.x.clear();
        line.y.clear();

        QList<QString> c = content->at(posInList).split(" ");
        c.removeAll("");
        long int count = c.at(0).toDouble();
        long int type = c.at(1).toDouble();

        for(int i=posInList+1; i<posInList+count+1; i++)
        {
            c=content->at(i).split(" ");
            c.removeAll("");
            temp(0,0)=c.at(0).toDouble()-offsetMatrix(0,0);
            temp(1,0)=c.at(1).toDouble()-offsetMatrix(0,1);
            temp(2,0)=c.at(2).toDouble()-offsetMatrix(0,2);
            temp=rotationMatrix*temp;
            if ((type==0 && mode==false)||type>0)
            {
                line.x.append(temp(0,0));
                line.y.append(temp(1,0));
            }
            else
            {
                point.x=temp(0,0);
                point.y=temp(1,0);
            }
        }

        switch (type){
        case 0:
            if (mode==false)
                Trajgrad->append(line);
            else
                MolgraphPoints->append(point);
            break;
        case 1:
            MolgraphBass1->append(line);
            break;
        case 2:
            MolgraphBass2->append(line);
            break;
        case 3:
            MolgraphConn->append(line);
            break;
        default:
            break;
        }
        posInList=posInList+count+1;

    }
    return 1;
}

bool GraphicsData::GetAtomsData(double cutOff)
{
	long int posInList=1;
    long int atoms=-1;
    bool convertsionPass;
    UniversalLines line;// = new UniversalLines();
    MatrixXd temp(3,1);
    QList<QString> c = content->at(posInList).split(" ");
    line.x.clear();
    line.y.clear();
    c.removeAll("");
    long int cellSize = c.at(0).toDouble();

    posInList=posInList+cellSize+1;
    int i=0;
    while (i<content->count())
    {
        if (content->at(i).contains("FUNCPLOT")){
            atoms=i;
            break;
        }
        i++;
    }

    if (atoms==-1)
        return 0;

    c=content->at(atoms+1).split(" ");
    c.removeAll("");
    cellSize=c.at(0).toDouble();
    atoms+=2;
    for (int i=atoms; i<atoms+cellSize; i++)
    {
        c=content->at(i).split(" ");
        c.removeAll("");
        temp(0,0)=c.at(0).toDouble()-offsetMatrix(0,0);
        temp(1,0)=c.at(1).toDouble()-offsetMatrix(0,1);
        temp(2,0)=c.at(2).toDouble()-offsetMatrix(0,2);
        temp=rotationMatrix*temp;
        if (abs(temp(2,0))<cutOff)
        {
            if (temp(0,0)>=frameLoc[0] && temp(0,0)<=frameLoc[1] && temp(1,0)>=frameLoc[2] && temp(1,0)<=frameLoc[3])
            {
                line.x.append(temp(0,0));
                line.y.append(temp(1,0));
            }
        }
    }
    Atoms->append(line);
    return 1;
}
