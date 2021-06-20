#include "fileread.h"

void read_file_from_fs(const QString& filename,QList<QString> *content)
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
