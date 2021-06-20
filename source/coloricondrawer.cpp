#include "coloricondrawer.h"

ColorIconDrawer::ColorIconDrawer()
{

}

QPixmap ColorIconDrawer::drawIcon(QColor choosenColor)
{
    QPixmap colorIcon(16,16);
    colorIcon.fill(Qt::transparent);
    QPainter p(&colorIcon);
    p.setRenderHint(QPainter::Antialiasing, true);
    QPen pen(Qt::transparent, 2);
    p.setPen(pen);
    QBrush brush(Qt::black);
    p.setBrush(brush);
    p.drawEllipse(0, 0, 16, 16);
    brush.setColor(choosenColor);
    p.setBrush(brush);
    p.drawEllipse(1, 1, 14, 14);
    return colorIcon;
}
