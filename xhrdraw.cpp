#include "xhrdraw.h"
#include "src/headers/graph.hpp"

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

void XHRDraw::drawLine(QGraphicsView* view, std::vector<std::vector<double>>* lines, QColor color, int thickness) {
    // get the scene associated with the graphics view
    QGraphicsScene* scene = view->scene();

    // create a new line item
    QGraphicsPathItem* path = new QGraphicsPathItem();

    // create a QPainterPath object to store the points
    QPainterPath pathPoints;

    // add the lines to path
    for (const auto& line : *lines) {
        pathPoints.moveTo(line[0], line[1]);
        pathPoints.lineTo(line[2], line[3]);
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

    std::vector<std::vector<double>> lines;

    // compute scale factors
    double scaleX = viewWidth / (graph.getMaxX() - graph.getMinX());
    double scaleY = viewHeight / (graph.getMaxY() - graph.getMinY());

    // iterate through the vertices and edges of the graph and add them to the scene
    for (auto& vertex : graph.getVertices()) {
        // scale to screen size
        double scaledX = (vertex.getX() - graph.getMinX()) * scaleX;
        double scaledY = (vertex.getY() - graph.getMinY()) * scaleY;

//        std::cout<<scaledX<< " " << scaledY << std::endl;

        // draw vertex
//        XHRDraw::drawCircle(graphicsView, scaledX, scaledY, 1, Qt::red);
        progressBarWindow->updateProgress(++progress);

        // iterate through the adjacency list of the vertex and add edges to the scene
        for (auto& adjacent_vertex_id : vertex.getAdjacencyList()) {

            // get coords
            auto adjacent_vertex = graph.getVertexById(adjacent_vertex_id);

            // scale to screen size
            double scaledX2 = (adjacent_vertex.getX() - graph.getMinX()) * scaleX;
            double scaledY2 = (adjacent_vertex.getY() - graph.getMinY()) * scaleY;

            // add adjacency lines to vector
            lines.push_back({scaledX,scaledY,scaledX2,scaledY2});

            progressBarWindow->updateProgress(++progress);
        }
    }

    //draw lines
    XHRDraw::drawLine(graphicsView,&lines,Qt::yellow,1);
}
