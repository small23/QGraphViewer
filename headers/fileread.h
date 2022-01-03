// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#ifndef FILEREAD_H
#define FILEREAD_H
#include <QString>
#include <QTextStream>
#include "QFile"

//Функция чтения данных из текстовых файлов
//filename - полный путь до файла и имя файла
//content - указатель на переменную с массивом для хранения
void readFileFromFs(const QString& filename,QList<QString> *content);

#endif // FILEREAD_H
