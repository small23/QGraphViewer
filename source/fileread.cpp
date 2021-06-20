#include "fileread.h"

void ReadFileFromFS(QString filename,QList<QString> *content)
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
