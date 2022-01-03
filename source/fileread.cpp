// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "fileread.h"

void readFileFromFs(const QString& filename,QList<QString> *content)
{
    content->clear();
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        //content=nullptr;
        throw "Error reading file! Can`t open!";
    }
    QTextStream instream(&file);
    while (!instream.atEnd())
        content->append(instream.readLine());

}
