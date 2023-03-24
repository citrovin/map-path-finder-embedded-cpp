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
    static void drawEdgeWithData(QGraphicsView* view, int x1, int y1, int x2, int y2, QColor color, double thickness, QVariant id, QVariant street_name, QVariant length);
    static void drawGraph(QGraphicsView* graphicsView, QString fileName, int viewWidth, int viewHeight, Graph graph, ProgressBar* progressBarWindow, bool streetData);
    static void drawNavPath(QGraphicsView* g, std::vector<Vertex> v, Graph graph_n, int viewWidth, int viewHeight);
};

#endif // XHRDRAW_H
