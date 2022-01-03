// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#ifndef PDOSPARSER_H
#define PDOSPARSER_H

//Класс парсинга PDOS файла и нахождения номеров функций

#include <QObject>
#include <QWidget>
#include <structuresHeaders.h>
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

    QVector<QVector<AtomTypes>> getAtomData(QList<QString> *content) const;
};

#endif // PDOSPARSER_H
