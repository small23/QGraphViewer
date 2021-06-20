#include "filessaver.h"


FilesSaver::FilesSaver() = default;


bool FilesSaver::SaveDosData(const QString& sourceFileLocation, BandData *bandData)
{
    for (int ii=0; ii<3; ii++)
    {
        QVector<QVector<double>> *data;
        QString folderName;
        switch (ii)
        {
        case 0:
            data=&(bandData->outputCOHP);
            folderName="COHP";
            break;

        case 1:
            data=&(bandData->outputCOOP);
            folderName="COOP";
            break;

        case 2:
            data=&(bandData->outputDOSS);
            folderName="DOSS";
            break;
        default:
            return 0;
        }
        if (data->count()>0)
        {
            QString path;
            QString pathFull;
            QStringList pathTemp;
            pathTemp=sourceFileLocation.split("/");

            for (int i=0; i<pathTemp.count()-1; i++)
                path+=pathTemp.at(i)+"/";
            path+=folderName;
            QDir dir(path);
            if (!dir.exists())
                dir.mkpath(".");

            for (int i=0; i<data->count(); i++)
            {
                if (i==data->count()-1)
                    pathFull=path+"/DOS_tot.txt";
                else
                    pathFull=path+"/"+QString::number(i+1)+".txt";
                QFile file(pathFull);
                QString outputStr="";
                if(file.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    // We're going to streaming text to the file
                    QTextStream stream(&file);

                    for (int j=0; j<bandData->oXDoss.count(); j++)
                    {
                        outputStr+=QString::number(bandData->oXDoss[j],'g',8)+"\t"+QString::number(data->at(i).at(j),'g',8)+"\n";
                    }
                    stream<<outputStr;
                    file.close();
                }
                else
                {
                    errorData.ErrorReason=0;
                    errorData.ErrorFile=sourceFileLocation;
                    return 0;
                }
            }
            pathFull=path+"/Fermi.txt";
            QFile file(pathFull);
            QString outputStr;
            if(file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                // We're going to streaming text to the file
                QTextStream stream(&file);
                outputStr=QString::number(bandData->fermi,'g',8)+"\t"+QString::number(0)+"\n"+QString::number(bandData->fermi,'g',8)+"\t"+QString::number(100);
                stream<<outputStr;
                file.close();
            }
            else
            {
                errorData.ErrorReason=0;
                errorData.ErrorFile=sourceFileLocation;
                return 0;
            }
        }

    }
    return 1;
}

bool FilesSaver::saveBANDData(QString fileName, BandData *bandData, double zoneMin, double zoneMax, bool uhf)
{
    QFileInfo info(fileName);
    QString path = info.absolutePath() + "/Band";
    QDir dir(path);
    if (!dir.exists())
        dir.mkpath(".");
    if (!uhf)
    {
        for (int i = 0; i < bandData->outputBAND.count(); i++)
        {
            fileName = path + "/" + QString::number(i + 1) + ".txt";
            QFile file(fileName);
            QString outputStr = "";
            if (file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                // We're going to streaming text to the file
                QTextStream stream(&file);

                for (int j = 0; j < bandData->oXBand.count(); j++)
                {
                    outputStr += QString::number(bandData->oXBand[j], 'g', 8) + "\t" + QString::number(bandData->outputBAND[i][j], 'g', 8) + "\n";
                }
                stream << outputStr;
                file.close();
            }
            else
            {
                errorData.ErrorReason = 0;
                errorData.ErrorFile = fileName;
                return 0;
            }
        }
    }
    else
    {
        QString pathTemp = path + "/Band_1/";
        QDir dir(pathTemp);
        if (!dir.exists())
            dir.mkpath(".");
        bool sucsess = saveLinFermi(pathTemp, bandData, zoneMin, zoneMax, uhf);
        if (!sucsess) return 0;
    	for (int i = 0; i < bandData->outputBAND.count(); i++)
        {
            fileName = pathTemp + QString::number(i + 1) + ".txt";
            QFile file(fileName);
            QString outputStr = "";
            if (file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                // We're going to streaming text to the file
                QTextStream stream(&file);

                for (int j = 0; j < bandData->oXBand.count()/2; j++)
                {
                    outputStr += QString::number(bandData->oXBand[j], 'g', 8) + "\t" + QString::number(bandData->outputBAND[i][j], 'g', 8) + "\n";
                }
                stream << outputStr;
                file.close();
            }
            else
            {
                errorData.ErrorReason = 0;
                errorData.ErrorFile = fileName;
                return 0;
            }
        }
        pathTemp = path + "/Band_2/";
        dir.setPath(pathTemp);
        if (!dir.exists())
            dir.mkpath(".");
        sucsess = saveLinFermi(pathTemp, bandData, zoneMin, zoneMax, uhf);
        if (!sucsess) return 0;
        for (int i = 0; i < bandData->outputBAND.count(); i++)
        {
            fileName = pathTemp + QString::number(i + 1) + ".txt";
            QFile file(fileName);
            QString outputStr = "";
            if (file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                // We're going to streaming text to the file
                QTextStream stream(&file);

                for (int j = bandData->oXBand.count() / 2; j < bandData->oXBand.count(); j++)
                {
                    outputStr += QString::number(bandData->oXBand[j - bandData->oXBand.count() / 2], 'g', 8) + "\t" + QString::number(bandData->outputBAND[i][j], 'g', 8) + "\n";
                }
                stream << outputStr;
                file.close();
            }
            else
            {
                errorData.ErrorReason = 0;
                errorData.ErrorFile = fileName;
                return false;
            }
        }
    }
    return true;
}

bool FilesSaver::saveLinFermi(const QString& path, BandData *bandData, const double zoneMin, const double zoneMax, const bool uhf)
{
    QString fileName = path + "/Fermi.txt";
    QFile file(fileName);
    QString outputStr;
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // We're going to streaming text to the file
        QTextStream stream(&file);
        if (uhf)
            outputStr = QString::number(bandData->oXBand[0], 'g', 8) + "\t" + QString::number(bandData->fermi, 'g', 8) + "\n" + QString::number(bandData->oXBand.at(bandData->oXBand.count() / 2 - 1), 'g', 8) + "\t" + QString::number(bandData->fermi, 'g', 8);
        else
			outputStr = QString::number(bandData->oXBand[0], 'g', 8) + "\t" + QString::number(bandData->fermi, 'g', 8) + "\n" + QString::number(bandData->oXBand.at(bandData->oXBand.count() / 2 - 1), 'g', 8) + "\t" + QString::number(bandData->fermi, 'g', 8);
        stream << outputStr;
        file.close();
    }
    else
    {
        errorData.ErrorReason = 0;
        errorData.ErrorFile = fileName;
        return false;
    }

    fileName = path + "/lin.xlsx";
    QXlsx::Document xlsx;

    for (int j = 0; j < (uhf ? bandData->kPoints.count() / 2 : bandData->kPoints.count()); j++)
    {
        xlsx.write(j * 2 + 1, 1, bandData->kPoints[j]);
        xlsx.write(j * 2 + 2, 1, bandData->kPoints[j]);
        if (zoneMin != 0 && zoneMax != 0)
        {
            xlsx.write(j * 2 + 1, 2, zoneMin);
            xlsx.write(j * 2 + 2, 2, zoneMax);
        }
    }
    QApplication::processEvents();
    const bool success = xlsx.saveAs(fileName); // save the document as 'Test.xlsx'
    if (success != true)
    {
        errorData.ErrorReason = 0;
        errorData.ErrorFile = fileName;
        return false;
    }
    return true;
}

bool FilesSaver::saveMAPNData(const QString& sourceFileLocation, BandData *bandData, int rotate)
{
    bandData->RotateData(rotate);
    QProgressDialog progressBar;
    progressBar.setValue(0);
    progressBar.setRange(0,bandData->outputMAPN.count());
    progressBar.setWindowModality(Qt::WindowModal);
    progressBar.show();
    QString path;
    QString pathFull;
    const QStringList pathTemp = sourceFileLocation.split("/");

    for (int i=0; i<pathTemp.count()-1; i++)
        path+=pathTemp.at(i)+"/";
    path+="Ro";
    QDir dir(path);
    if (!dir.exists())
        dir.mkpath(".");
    for(int i=0; i<bandData->outputMAPN.count(); i++)
    {
        progressBar.setValue(i);
        progressBar.update();
        switch (i){
        case 0:
            pathFull=path+"/Ro-"+QString::number(rotate)+".xlsx";
            break;
        case 1:
            if (bandData->type==0 || bandData->type==2)
            {
                pathFull=path+"/Ro_Def-"+QString::number(rotate)+".xlsx";
            }
            else
            {
                pathFull=path+"/Spin-"+QString::number(rotate)+".xlsx";
            }
            break;
        case 2:
            pathFull=path+"/Ro_Def-"+QString::number(rotate)+".xlsx";
            break;
        case 3:
            pathFull=path+"/Spin_Def-"+QString::number(rotate)+".xlsx";
            break;
        default:
            progressBar.close();
            return 0;
        }

        QXlsx::Document xlsx;
        for (int j=0; j<bandData->outputMAPN[i].count(); j++)
        {
            xlsx.write(j+1,1,bandData->oYMapn[j]);
            xlsx.write(j+1,2,bandData->oXMapn[j]);
            xlsx.write(j+1,3,bandData->outputMAPN[i][j]);
        }
        QApplication::processEvents();
//            QThread *thread= new QThread;
//            XlsxSaver *saveDoc = new XlsxSaver(&xlsx,pathFull);
//            saveDoc->moveToThread(thread);
//            thread->start();
//            while (thread->isRunning());
        bool success=xlsx.saveAs(pathFull); // save the document as 'Test.xlsx'
        if (success!=true)
        {
            progressBar.close();
            errorData.ErrorReason=0;
            errorData.ErrorFile=sourceFileLocation;
            return 0;
        }
    }
    progressBar.close();
    return 1;
}

bool FilesSaver::saveCryTopData()
{

    return 1;
}
