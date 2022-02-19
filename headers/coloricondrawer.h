// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#ifndef COLORICONDRAWER_H
#define COLORICONDRAWER_H

//Класс отрисовки Pixmap разного цвета

#include "QPixmap"
#include "QColor"
#include "QPainter"
#include <qcoreapplication.h>
#include "constantsandstrings.h"

class ColorIconDrawer
{
public:
    ColorIconDrawer();
    //Метод отрисовки новых иконок, принимает на вход цвет
    static QPixmap drawIcon(const QColor& color, qreal devPixRat);
};

#endif // COLORICONDRAWER_H
