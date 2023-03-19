#ifndef XHRDRAW_H
#define XHRDRAW_H

#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsEllipseItem>

#include "progressbar.h"
#include "src/headers/graph.hpp"

class XHRDraw
{
public:
    static void drawCircle(QGraphicsView* view, int x, int y, int r, const QColor& color);
    static void drawLine(QGraphicsView* view, std::vector<std::vector<double>>* points, QColor color, int thickness);
    static void updateView(QGraphicsView* view);
    static void drawGraph(QGraphicsView* graphicsView, QString fileName, int viewWidth, int viewHeight, Graph graph, ProgressBar* progressBarWindow);
};

#endif // XHRDRAW_H
