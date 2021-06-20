#ifndef PDOSPARSER_H
#define PDOSPARSER_H

//Класс парсинга PDOS файла и нахождения номеров функций

#include <QObject>
#include <QWidget>
#include <StructuresHeaders.h>
#include "QFile"
#include "QFileDialog"
#include "QMessageBox"

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

class PdosParser : public QWidget
{
    Q_OBJECT
public:
    explicit PdosParser(QWidget *parent = nullptr);

    QVector<QVector<AtomTypes>> getAtomData(QList<QString> *content);
};

#endif // PDOSPARSER_H
