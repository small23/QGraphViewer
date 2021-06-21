#include "crystaltopondconvertors.h"

CrystalTopondConvertors::CrystalTopondConvertors() = default;

bool CrystalTopondConvertors::convertCrystalToTopond(QList<QString> *content)
{
    int coords=-1,counter=0;
    QString c;
    QString useless;
    output="";
    double temp1,temp2,temp3;
    QVector<QVector<double>> atoms;
    QVector<double> tempAtomLine;
    while (counter<content->count())
    {
        if (content->at(counter).contains("COORDINATES OF THE 3 POINTS (BOHR):"))
            coords=counter;
        counter++;
    }
    if (coords==-1)
        return false;
    QTextStream getData(&c);
    for (int i=0; i<3; i++)
    {
        tempAtomLine.clear();
        c=content->at(coords+1+i);
        c.remove(0,16);
        getData.setString(&c);
        getData >> temp1 >> temp2 >> temp3;
        tempAtomLine.append(temp1);
        tempAtomLine.append(temp2);
        tempAtomLine.append(temp3);
        atoms.append(tempAtomLine);
    }

    double ab = sqrt(pow(atoms[0][0]-atoms[1][0],2)+pow(atoms[0][1]-atoms[1][1],2)+pow(atoms[0][2]-atoms[1][2],2));
    double cb = sqrt(pow(atoms[2][0]-atoms[1][0],2)+pow(atoms[2][1]-atoms[1][1],2)+pow(atoms[2][2]-atoms[1][2],2));

    ab*=0.529177208;
    cb*=0.529177208;

    output.append("TOPO\nPL2D\n0\n");
    output.append(QString::number(atoms[0][0])+","+QString::number(atoms[0][1])+","+QString::number(atoms[0][2])+"\n");
    output.append("0\n");
    output.append(QString::number(atoms[1][0])+","+QString::number(atoms[1][1])+","+QString::number(atoms[1][2])+"\n");
    output.append("0\n");
    output.append(QString::number(atoms[2][0])+","+QString::number(atoms[2][1])+","+QString::number(atoms[2][2])+"\n");
    output.append("3\n0\n60,15.0\n1                          ICONT=1\n");
    output.append("0,"+QString::number(ab, 'f',4)+",0.05\n");
    output.append("0,"+QString::number(cb, 'f',4)+",0.05\n");
    output.append("1,1,1,1,1,1,1,1,1,1,1,0    IFU 1-11 set to 1\nName\n0.55                       SCALE=0.55\n0.1,0.1,0                  TOLER=0.1, TR1=0.1, IPLANE=0\n");
    output.append("2.2,1,1,1                  THR=2.2, IL vector all set to 1\n36,0                       NPATH=36, NEXTR=0\nEND");
    return true;
}

bool CrystalTopondConvertors::convertTopondToCrystal(QList<QString> *content)
{
    int xAxis=-1, coords=-1,counter=0;
    QString c;
    QString useless;
    output="";
    double temp1,temp2,temp3;
    QVector<QVector<double>> convertorData;
    QVector<double> tempAtomLine;
    while (counter<content->count())
    {
        if (content->at(counter).contains("COORD.,AT. N., CELL OF ATOMS A,B,C"))
            coords=counter;
        else if(content->at(counter).contains("X AXIS RANGES AND INCREMENTS (ANG)"))
            xAxis=counter;
        counter++;
    }
    if (coords==-1)
        return false;
    if (xAxis==-1)
        return false;
    QTextStream getData(&c);
    for (int i=0; i<3; i++)
    {
        tempAtomLine.clear();
        c=content->at(coords+i);
        c.remove(0,37);
        getData.setString(&c);
        getData >> temp1 >> temp2 >> temp3;
        tempAtomLine.append(temp1);
        tempAtomLine.append(temp2);
        tempAtomLine.append(temp3);
        convertorData.append(tempAtomLine);
    }

    for (int i=0; i<2; i++)
    {
        tempAtomLine.clear();
        c=content->at(xAxis+i);
        c.remove(0,37);
        getData.setString(&c);
        getData >> temp1 >> temp2 >> temp3;
        tempAtomLine.append(temp1);
        tempAtomLine.append(temp2);
        tempAtomLine.append(temp3);
        convertorData.append(tempAtomLine);
    }

    double xab,xcb,yab,ycb,zab,zcb,xac,yac,zac;
    double AB, CB, AC, pnm, A, B, C;
    double pn1, pn2, pn3, alpha, fi, h1, h2, h3;
    double x, y, z, d, xm, ym, zm, ADM, ABM, BCM, CDM;

    xab=convertorData[0][0]-convertorData[1][0];
    xcb=convertorData[2][0]-convertorData[1][0];
    yab=convertorData[0][1]-convertorData[1][1];
    ycb=convertorData[2][1]-convertorData[1][1];
    zab=convertorData[0][2]-convertorData[1][2];
    zcb=convertorData[2][2]-convertorData[1][2];
    xac=convertorData[0][0]-convertorData[2][0];
    yac=convertorData[0][1]-convertorData[2][1];
    zac=convertorData[0][2]-convertorData[2][2];

    AB=sqrt(pow(xab,2)+pow(yab,2)+pow(zab,2));
    CB=sqrt(pow(xcb,2)+pow(ycb,2)+pow(zcb,2));
    AC=sqrt(pow(xac,2)+pow(yac,2)+pow(zac,2));

    A=yab*zcb-zab*ycb;
    B=zab*xcb-xab*zcb;
    C=xab*ycb-yab*xcb;
    pnm=sqrt(pow(A,2)+pow(B,2)+pow(C,2));

    pn1=A/pnm;
    pn2=B/pnm;
    pn3=C/pnm;

    alpha=acos((pow(AB,2)+pow(CB,2)-pow(AC,2))/(2*AB*CB));

    fi=3.14159265358979323846/2-alpha;

    d=xcb*pn1+ycb*pn2+zcb*pn3;
    h1=pn2*zcb-pn3*ycb;
    h2=pn3*xcb-pn1*zcb;
    h3=pn1*ycb-pn2*xcb;

    x=pn1*d*(1-cos(fi))+h1*sin(fi)+xcb*cos(fi);
    y=pn2*d*(1-cos(fi))+h2*sin(fi)+ycb*cos(fi);
    z=pn3*d*(1-cos(fi))+h3*sin(fi)+zcb*cos(fi);

    xm=x+convertorData[1][0];
    ym=y+convertorData[1][1];
    zm=z+convertorData[1][2];

    for (int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
            convertorData[i][j]*=0.529177208;
    }

    xm=xm*0.529177208;  ym=ym*0.529177208;  zm=zm*0.529177208;

    AB=AB*0.529177208;
    CB=CB*0.529177208;

    ADM= - convertorData[3][0];
    ABM= - convertorData[4][0];
    BCM= convertorData[3][1]-AB;
    CDM= convertorData[4][1]-CB;

    output.append("ECHG\n0\n200\nCOORDINA\n");
    output.append(QString::number(convertorData[0][0])+" "+QString::number(convertorData[0][1])+" "+QString::number(convertorData[0][2])+"\n");
    output.append(QString::number(convertorData[1][0])+","+QString::number(convertorData[1][1])+","+QString::number(convertorData[1][2])+"\n");
    output.append(QString::number(xm)+","+QString::number(ym)+","+QString::number(zm)+"\n");
    output.append("MARGINS\n");
    output.append(QString::number(ABM)+" "+QString::number(CDM)+" "+QString::number(ADM)+" "+QString::number(BCM)+"\n");
    output.append("END\nPATO\n0 0\n");
    output.append("ECHG\n0\n200\nCOORDINA\n");
    output.append(QString::number(convertorData[0][0])+" "+QString::number(convertorData[0][1])+" "+QString::number(convertorData[0][2])+"\n");
    output.append(QString::number(convertorData[1][0])+","+QString::number(convertorData[1][1])+","+QString::number(convertorData[1][2])+"\n");
    output.append(QString::number(xm)+","+QString::number(ym)+","+QString::number(zm)+"\n");
    output.append("MARGINS\n");
    output.append(QString::number(ABM)+" "+QString::number(CDM)+" "+QString::number(ADM)+" "+QString::number(BCM)+"\n");
    output.append("END");

    return true;
}
