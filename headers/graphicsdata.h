#ifndef GRAPHICSDATA_H
#define GRAPHICSDATA_H

//Класс для парсинга и хранения данных
//Trajgrad, Molgraph, атомов

#include "StructuresHeaders.h"
#include <Eigen/Core>
#include <Eigen/Geometry>
#include "fileread.h"
#include "QMessageBox"

using namespace Eigen;
class GraphicsData
{
public:
    //Конструктор класса
    GraphicsData(): frameLoc{}, parsedFrameLoc(false), rotationMatrix(3, 3), offsetMatrix(1, 3), offsetGraph(2, 3)
    {
	    MolgraphConn = new QList<UniversalLines>;
	    MolgraphBass1 = new QList<UniversalLines>;
	    MolgraphBass2 = new QList<UniversalLines>;
	    MolgraphPoints = new QList<UniversalPoints>;
	    Trajgrad = new QList<UniversalLines>;
	    Atoms = new QList<UniversalLines>;
	    content = new QList<QString>;
    }
    //Метод парсинга данных, на вход принимается содержимое файла dat, и уровень отсечки
    //атомов после поворота в плоскость
    int GetAndParseMainData(QList<QString> fileFields, double cutOff);
    //метод очистки класса от данных
    void clear();
    //переменные-хранилища данных
    QList <UniversalLines> *Trajgrad;
    QList <UniversalLines> *MolgraphConn;
    QList <UniversalLines> *MolgraphBass1;
    QList <UniversalLines> *MolgraphBass2;
    QList <UniversalPoints> *MolgraphPoints;
    QList <UniversalLines> *Atoms;
    //Переменная-хранилище координат зоны отсечки
    double frameLoc[4];
    //Переменная флаг обнаружения зоны отсечки
    bool parsedFrameLoc;
private:

    MatrixXd rotationMatrix;
    MatrixXd offsetMatrix;
    MatrixXd offsetGraph;
    QList<QString> *content;
    //Вспомогательные переменные конвертации и получения данных
    bool GetOffsetAndTransMatrix();
    bool GetTrajgradMolgraphData(bool mode);
    bool GetAtomsData(double cutOff);
};

#endif // GRAPHICSDATA_H
