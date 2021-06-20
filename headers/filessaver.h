#ifndef FILESAVERCLASS_H
#define FILESAVERCLASS_H

//Класс сохранения сконвертированных данных
//В файлы, пригодыне для чтения Grafor

#include "QFile"
#include "QDir"
#include "QTextStream"
#include "QApplication"
#include "QProgressDialog"
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
#include "banddata.h"

class FilesSaver
{
public:
    FilesSaver();
    //Методы сохранения данных из различных источников
    bool saveBANDData(QString fileName, BandData* bandData, double zoneMin, double zoneMax, bool uhf);
    bool SaveDosData(const QString& sourceFileLocation, BandData *bandData);
    bool saveMAPNData(const QString& sourceFileLocation, BandData *bandData, int rotate);
    bool saveCryTopData();
    //Структура, сохраняющая возникающие ошибки при записи данных
    struct ErrorData
    {
        int ErrorReason=0; // 0=File write error
        QString ErrorFile="";
    };

    ErrorData errorData;

private:
    //Приватный метод сохранения файла с данными об уровне Ферми
    bool saveLinFermi(const QString& path, BandData* bandData, double zoneMin, double zoneMax, bool uhf);
};

#endif // FILESAVERCLASS_H
