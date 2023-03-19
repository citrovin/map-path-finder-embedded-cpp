#include "xhrdraw.h"
#include "src/headers/graph.hpp"

#include <QPainter>
#include <QGraphicsItem>

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
}

void XHRDraw::drawCircleFast(QGraphicsView* view, int x, int y, int r, const QColor& color)
{
    // Get the scene associated with the graphics view
    QGraphicsScene* scene = view->scene();

    // QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(x, y, r, r);

    // Create a new QPixmap object to draw on
    QPixmap pixmap(view->width(), view->height());
    pixmap.fill(color);

    // Create a QPainter object to draw on the QPixmap
    QPainter painter(&pixmap);

    // Set the pen color and thickness
    QPen pen(color);
    pen.setWidth(2);
    painter.setPen(pen);

    // Draw the ellipse on the QPixmap
    painter.drawEllipse(x, y, r, r);

    // Add the QPixmap as a QGraphicsPixmapItem to the scene
    QGraphicsPixmapItem* pixmapItem = scene->addPixmap(pixmap);

    // Set the position of the pixmap item to the top-left corner of the view
    pixmapItem->setPos(view->mapToScene(0, 0));
}

void XHRDraw::drawLine(QGraphicsView* view, std::vector<std::vector<double>>* lines, QColor color, int thickness) {
    // get the scene associated with the graphics view
    QGraphicsScene* scene = view->scene();

    // create a new line item
    QGraphicsPathItem* path = new QGraphicsPathItem();

    // create a QPainterPath object to store the points
    QPainterPath pathPoints;

    // add the lines to path
#pragma omp parallel for
    for (int i = 0; i < lines->size(); i++) {
        pathPoints.moveTo((*lines)[i][0], (*lines)[i][1]); // more thread safe
        pathPoints.lineTo((*lines)[i][2], (*lines)[i][3]); // more thread safe
//        std::cout<< i << std::endl;
    }

    // set the path of the path item
    path->setPath(pathPoints);

    // set the pen color to the given color and thickness
    QPen pen(color, thickness);
    path->setPen(pen);

    // add the path to the scene
    scene->addItem(path);
}

void XHRDraw::updateView(QGraphicsView* view) {
    view->update();
}


void XHRDraw::drawGraph(QGraphicsView* graphicsView, QString fileName, int viewWidth, int viewHeight, Graph graph, ProgressBar* progressBarWindow) {
    int progress = 0;
    int m = progressBarWindow->getMax();

    std::vector<std::vector<double>> lines;

    // compute scale factors
    double scaleX = viewWidth / (graph.getMaxX() - graph.getMinX());
    double scaleY = viewHeight / (graph.getMaxY() - graph.getMinY());

    auto verts = graph.getVertices();
    // iterate through the vertices and edges of the graph and add them to the scene
#pragma omp parallel for
    for (int i = 0; i < verts.size(); ++i) {
        // scale to screen size
        double scaledX = (verts[i].getX() - graph.getMinX()) * scaleX;
        double scaledY = (verts[i].getY() - graph.getMinY()) * scaleY;

//        std::cout<<scaledX<< " " << scaledY << std::endl;

        // draw vertex
        XHRDraw::drawCircle(graphicsView, scaledX, scaledY, 1, Qt::red);
//        std::cout << i << endl;
//        if (progress/progressBarWindow->getMax())
//        progressBarWindow->updateProgress(++progress);
//        progress++;
        // iterate through the adjacency list of the vertex and add edges to the scene
        for (auto& adjacent_vertex_id : verts[i].getAdjacencyList()) {

            // get coords
            auto adjacent_vertex = graph.getVertexById(adjacent_vertex_id);

            // scale to screen size
            double scaledX2 = (adjacent_vertex.getX() - graph.getMinX()) * scaleX;
            double scaledY2 = (adjacent_vertex.getY() - graph.getMinY()) * scaleY;

            // add adjacency lines to vector
            lines.push_back({scaledX,scaledY,scaledX2,scaledY2});
//            progress++;
//            progressBarWindow->updateProgress(++progress);
        }
    }

    //draw lines
    XHRDraw::drawLine(graphicsView,&lines,Qt::yellow,1);
}
