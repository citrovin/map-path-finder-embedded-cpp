#ifndef XHRDRAW_H
#define XHRDRAW_H

#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsEllipseItem>

class XHRDraw
{
public:
    static void drawCircle(QGraphicsView* view, int x, int y, int r, const QColor& color);
    static void drawLine(QGraphicsView* view, int x1, int y1, int x2, int y2, QColor color, int thickness);
};

#endif // XHRDRAW_H
