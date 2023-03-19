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
    static void drawCircle(QGraphicsView* view, int x, int y, double r, const QColor& color);
    static void drawCircleFast(QGraphicsView* view, int x, int y, double r, const QColor& color);
    static void drawLine(QGraphicsView* view, std::vector<std::vector<double>>* points, QColor color, double thickness);
    static void updateView(QGraphicsView* view);
    static void drawGraph(QGraphicsView* graphicsView, QString fileName, int viewWidth, int viewHeight, Graph graph, ProgressBar* progressBarWindow);
    static void drawVertexWithData(QGraphicsView* view, int x, int y, double r, const QColor& color, QVariant id);
};

#endif // XHRDRAW_H
