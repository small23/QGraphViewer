// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

#include "coloricondrawer.h"

ColorIconDrawer::ColorIconDrawer() = default;

#define SCALE_FACTOR (5.0)
#define ICON_SIZE    (16.0)
#define INNER_CIRQ   (13.0)


QPixmap ColorIconDrawer::drawIcon(const QColor& color, qreal devPixRat)
{
    QPixmap colorIcon(ICON_SIZE * SCALE_FACTOR, ICON_SIZE * SCALE_FACTOR);
    colorIcon.fill(Qt::transparent);
    QPainter p(&colorIcon);
    p.setRenderHint(QPainter::Antialiasing, true);
    const QPen pen(Qt::transparent, 2);
    p.setPen(pen);
    QBrush brush(Qt::black);
    p.setBrush(brush);
    p.drawEllipse(0, 0, ICON_SIZE * SCALE_FACTOR, ICON_SIZE * SCALE_FACTOR);
    brush.setColor(color);
    p.setBrush(brush);
    p.drawEllipse(((ICON_SIZE - INNER_CIRQ)/2) * SCALE_FACTOR, ((ICON_SIZE - INNER_CIRQ) / 2)* SCALE_FACTOR,
	INNER_CIRQ * SCALE_FACTOR, INNER_CIRQ * SCALE_FACTOR);
    colorIcon.setDevicePixelRatio(devPixRat);
    QPixmap colorIconOut = colorIcon.scaled(ICON_SIZE * devPixRat, ICON_SIZE * devPixRat, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    colorIconOut.setDevicePixelRatio(devPixRat);
    return colorIconOut;
}
