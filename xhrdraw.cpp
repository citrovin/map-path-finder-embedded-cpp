#include "xhrdraw.h"

void XHRDraw::drawCircle(QGraphicsView* view, int x, int y, int r, const QColor& color)
{
    // Get the scene associated with the graphics view
    QGraphicsScene* scene = view->scene();

    // Create a new ellipse item with the specified dimensions
    QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(x, y, r, r);

    // Set the pen color to red
    QPen pen(color);
    QBrush brush(color);
    ellipse->setPen(pen);
    ellipse->setBrush(brush);

    // Add the ellipse item to the scene
    scene->addItem(ellipse);

    // Update the graphics view to show the new ellipse
    view->update();
}

void XHRDraw::drawLine(QGraphicsView* view, int x1, int y1, int x2, int y2, QColor color, int thickness) {
    // Get the scene associated with the graphics view
    QGraphicsScene* scene = view->scene();

    // Create a new line item
    QGraphicsLineItem* line = new QGraphicsLineItem(x1,y1,x2,y2);

    // set the pen color to the given color and thickness
    QPen pen(color, thickness);
    line->setPen(pen);

    // Add the line item to the scene
    scene->addItem(line);

    // update scene
    view->update();
}
