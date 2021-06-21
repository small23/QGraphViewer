#ifndef CRYSTALTOPONDCONVERTORS_H
#define CRYSTALTOPONDCONVERTORS_H

//Класс конвертации конфигурационных файлов
//CRYSTAL в файлы TOPIND
//И наоборот с конвертацией координат и
//прочих параметров

#include <QList>
#include "QTextStream"
#include "QtMath"

class CrystalTopondConvertors
{
public:
    CrystalTopondConvertors();
    bool convertCrystalToTopond(QList<QString> *content);
    bool convertTopondToCrystal(QList<QString> *content);
    QString output;
};

#endif // CRYSTALTOPONDCONVERTORS_H
