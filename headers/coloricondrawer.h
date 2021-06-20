#ifndef COLORICONDRAWER_H
#define COLORICONDRAWER_H

//Класс отрисовки Pixmap разного цвета

#include "QPixmap"
#include "QColor"
#include "QPainter"

class ColorIconDrawer
{
public:
    ColorIconDrawer();
    //Метод отрисовки новых иконок, принимает на вход цвет
    static QPixmap draw_icon(const QColor& color);
};

#endif // COLORICONDRAWER_H
