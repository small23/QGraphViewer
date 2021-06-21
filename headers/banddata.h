#ifndef BANDDATA_H
#define BANDDATA_H

//Класс-парсер и хранилище данных для структур
//BAND: COOP, COHP, DOS, MAPN,
//Имеющих схожий общий файл сохранения

#include "QVector"
#include "QTextStream"

class BandData
{
public:
    //Конструктор класса
    BandData();
    //Метод парсинга данных из файла
    //Content содержит строки файла с данными, UHF определяет режим работы парсера
    void parseData(QList<QString> *content, bool uhf=false);
    //Метод обеспечивает поворот СК на величину до 270 градусов с шагом 90
    void rotateData(int angle);
    //Метод очистки данных
    void clear();
    //Метод посчета количества данных, хранящихся в классе
    static QVector<int>  countData(QList<QString> *content);
    //Переменные-хранилища обработанных данных
    QVector<QVector<double>> outputBAND, outputDOSS, outputCOHP, outputCOOP, outputMAPN;
    //Переменные-хранилища содержащие данные по СК
    QVector<double> kPoints, oXBand, oXMapn, oYMapn, oXDoss, oXCohp, oXCoop, oXTempMapn, oYTempMapn;
    //Переменная-хранилище границ OX, необходимых для отображения
    double borders[2];
    //УРовень ферми
    double fermi;
    //Переменная-хранилище префикста данных типа MAPN (к примеру %0MAPN)
    int type;
private:
    double nothing, interval;
    //Внутренние методы парсинга данных
    void parseBandData(QList<QString> *content, QVector<long> *indexList0Band);
    void parseDccpData(QList<QString> *content, QVector<long> *indexList, QVector<QVector<double>> *output, QVector<double> *oX);
    void parseMapnData(QList<QString> *content, QVector<long> *indexList, bool uhf);

};

#endif // BANDDATA_H
