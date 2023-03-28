#ifndef XHRDRAW_H
#define XHRDRAW_H

#include <QGraphicsView>
#include <QPainter>
#include <QGraphicsEllipseItem>

#include "src/headers/graph.hpp"

// a lib to draw the custom itmes and graphs
class XHRDraw
{
public:
    // draw a normal circle
    static void drawCircle(QGraphicsView* view, int x, int y, double r, const QColor& color);
    // draw a normal circle but faster
    static void drawCircleFast(QGraphicsView* view, int x, int y, double r, const QColor& color);
    // draw a path with n lines
    static void drawLine(QGraphicsView* view, std::vector<std::vector<double>>* points, QColor color, double thickness);
    // update the view
    static void updateView(QGraphicsView* view);
    // draw a graph
    static void drawGraph(QGraphicsView* graphicsView, QString fileName, int viewWidth, int viewHeight, Graph graph);
    // OVERLOAD draw a graph with street data
    static void drawGraph(QGraphicsView* graphicsView, QString fileName, int viewWidth, int viewHeight, Graph graph, bool streetData);
    // draw a vertex with id
    static void drawVertexWithData(QGraphicsView* view, int x, int y, double r, const QColor& color, QVariant id);
    // OVERLOAD draw a vertex with id and label
    static void drawVertexWithData(QGraphicsView* view, int x, int y, double r, const QColor& color, QVariant id, QVariant label);
    // draw an edge with data
    static void drawEdgeWithData(QGraphicsView* view, int x1, int y1, int x2, int y2, QColor color, double thickness, QVariant id, QVariant label, QVariant street_name, QVariant length);
    // draw the path from the vector list
    static void drawNavPath(QGraphicsView* g, std::vector<Vertex> v, Graph graph_n, int viewWidth, int viewHeight);
    // draw all visited points in the vector list
    static void drawNavPathVisited(QGraphicsView* g, std::vector<Vertex> v, Graph graph_n, int viewWidth, int viewHeight);
    // clear the view of all items
    static void clearItems(QGraphicsView* view);
    // clear the view of all items labeled as label
    static void clearItems(QGraphicsView* view, std::string label);
};

#endif // XHRDRAW_H
