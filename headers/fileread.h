#ifndef FILEREAD_H
#define FILEREAD_H
#include <QString>
#include <QTextStream>
#include "QFile"

//Функция чтения данных из текстовых файлов
//filename - полный путь до файла и имя файла
//content - указатель на переменную с массивом для хранения
void read_file_from_fs(const QString& filename,QList<QString> *content);

#endif // FILEREAD_H
