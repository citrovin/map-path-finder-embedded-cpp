#include "xhrdraw.h"
#include "src/headers/graph.hpp"

#include <QPainter>
#include <QGraphicsItem>
#include <QVariant>

class VertexEllipseItem : public QGraphicsEllipseItem
{
    public:
        VertexEllipseItem(const QRectF& rect, QGraphicsItem* parent = nullptr) : QGraphicsEllipseItem(rect, parent) {
                setAcceptHoverEvents(true);
        }

        // Override the hover events to change the color when hovering
        void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override
        {
//            setPen(QPen(Qt::green));
//            setBrush(QBrush(Qt::green));
            QGraphicsEllipseItem::hoverEnterEvent(event);
        }

        void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override
        {
//            setPen(QPen(Qt::red));
//            setBrush(QBrush(Qt::red));
            QGraphicsEllipseItem::hoverLeaveEvent(event);
        }
};

void XHRDraw::drawCircle(QGraphicsView* view, int x, int y, double r, const QColor& color)
{
    // Get the scene associated with the graphics view
    QGraphicsScene* scene = view->scene();

    // Create a new ellipse item with the specified dimensions
    QGraphicsEllipseItem* ellipse = new QGraphicsEllipseItem(QRectF(x - r/2, y - r/2, r, r));

    // draw above lines
    ellipse->setZValue(1);

    // Set the pen color to red
    QPen pen(color);
    QBrush brush(color);
    ellipse->setPen(pen);
    ellipse->setBrush(brush);

    // Add the ellipse item to the scene
    scene->addItem(ellipse);
}

void XHRDraw::drawCircleFast(QGraphicsView* view, int x, int y, double r, const QColor& color)
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
    painter.drawEllipse(QRectF(x, y, r, r));

    // Add the QPixmap as a QGraphicsPixmapItem to the scene
    QGraphicsPixmapItem* pixmapItem = scene->addPixmap(pixmap);

    // Set the position of the pixmap item to the top-left corner of the view
    pixmapItem->setPos(view->mapToScene(0, 0));
}

void XHRDraw::drawVertexWithData(QGraphicsView* view, int x, int y, double r, const QColor& color, QVariant id)
{
    // Get the scene associated with the graphics view
    QGraphicsScene* scene = view->scene();

    // Create a new ellipse item with the specified dimensions
    VertexEllipseItem* ellipse = new VertexEllipseItem(QRectF(x - r/2, y - r/2, r, r));

    // draw above lines
    ellipse->setZValue(1);

    // Set the pen color to red
    QPen pen(color);
    QBrush brush(color);
    pen.setBrush(brush);
    ellipse->setPen(pen);
    ellipse->setBrush(brush);
    ellipse->setData(0, id);

    // select
    ellipse->setFlag(QGraphicsItem::ItemIsSelectable, true);
    ellipse->setVisible(true);

    // Add the ellipse item to the scene
    scene->addItem(ellipse);
}

// this doesn't allow to display street names because we only have one path item, instead of all edge items, but it's faster
void XHRDraw::drawLine(QGraphicsView* view, std::vector<std::vector<double>>* lines, QColor color, double thickness) {
    // get the scene associated with the graphics view
    QGraphicsScene* scene = view->scene();

    // create a new line item
    QGraphicsPathItem* path = new QGraphicsPathItem();

    // draw below points
    path->setZValue(0);

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
    QPen pen(color);
    pen.setWidthF(thickness);
    path->setPen(pen);
    path->setFlag(QGraphicsItem::ItemIsSelectable, false);

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

    auto verts = graph.getVertices();
    // iterate through the vertices and edges of the graph and add them to the scene
#pragma omp parallel for
    for (int i = 0; i < verts.size(); ++i) {
        // scale to screen size
        double scaledX = std::round((verts[i].getX() - graph.getMinX()) * scaleX );
        double scaledY = std::round((verts[i].getY() - graph.getMinY()) * scaleY );

//        std::cout<<scaledX<< " " << scaledY << std::endl;

        // draw vertex
        XHRDraw::drawVertexWithData(graphicsView, scaledX, scaledY, 0.2, Qt::red, verts[i].getId());
//        std::cout << i << endl;
//        if (progress/progressBarWindow->getMax())
//        progressBarWindow->updateProgress(++progress);
//        progress++;
        // iterate through the adjacency list of the vertex and add edges to the scene
        for (auto& adjacent_vertex_id : verts[i].getAdjacencyList()) {

            // get coords
            auto adjacent_vertex = graph.getVertexById(adjacent_vertex_id);

            // scale to screen size
            double scaledX2 = std::round((adjacent_vertex.getX() - graph.getMinX()) * scaleX );
            double scaledY2 = std::round((adjacent_vertex.getY() - graph.getMinY()) * scaleY );

            // add adjacency lines to vector
            lines.push_back({scaledX,scaledY,scaledX2,scaledY2});
//            progress++;
//            progressBarWindow->updateProgress(++progress);
        }
    }

    //draw lines
    XHRDraw::drawLine(graphicsView,&lines,Qt::black,0.2);
}
