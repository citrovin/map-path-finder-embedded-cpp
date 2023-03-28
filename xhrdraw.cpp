#include "xhrdraw.h"
#include "src/headers/graph.hpp"

#include <QPainter>
#include <QGraphicsItem>
#include <QVariant>
#include <QToolTip>
#include <QGraphicsSceneMouseEvent>

class VertexEllipseItem : public QGraphicsEllipseItem
{
    public:
        VertexEllipseItem(const QRectF& rect, QGraphicsItem* parent = nullptr) : QGraphicsEllipseItem(rect, parent) {
                setAcceptHoverEvents(true);
        }

        // override the hover events to change the color when hovering
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

class EdgeLineItem : public QGraphicsLineItem
{
public:
    EdgeLineItem(double x1, double y1, double x2, double y2, QGraphicsItem *parent = nullptr)
        : QGraphicsLineItem(x1, y1, x2, y2, parent)
    {
        setAcceptHoverEvents(true);
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override
    {
        QGraphicsLineItem::mousePressEvent(event);
        QToolTip::showText(event->screenPos(), toolTip());
    }

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override
    {
        setPen(QPen(Qt::green,0.5));
//        std::cout<<data(1).toString().toStdString()<<std::endl;
        QGraphicsLineItem::hoverEnterEvent(event);
    }

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override
    {
        setPen(QPen(Qt::black,0.2));
        QGraphicsLineItem::hoverEnterEvent(event);
    }
};

class NavEdgeLineItem : public QGraphicsLineItem
{
public:
    NavEdgeLineItem(double x1, double y1, double x2, double y2, QGraphicsItem *parent = nullptr)
        : QGraphicsLineItem(x1, y1, x2, y2, parent)
    {
        setAcceptHoverEvents(true);
    }

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override
    {
        QGraphicsLineItem::mousePressEvent(event);
        QToolTip::showText(event->screenPos(), toolTip());
    }

    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override
    {
        setPen(QPen(Qt::yellow,0.7));
//        std::cout<<data(1).toString().toStdString()<<std::endl;
        QGraphicsLineItem::hoverEnterEvent(event);
    }

    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override
    {
        setPen(QPen(Qt::green,0.5));
        QGraphicsLineItem::hoverEnterEvent(event);
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

void XHRDraw::drawVertexWithData(QGraphicsView* view, int x, int y, double r, const QColor& color, QVariant id, QVariant label)
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
    ellipse->setData(1, label);

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

void XHRDraw::drawEdgeWithData(QGraphicsView* view, int x1, int y1, int x2, int y2, QColor color, double thickness, QVariant id, QVariant label, QVariant street_name, QVariant length) {
    // get the scene associated with the graphics view
    QGraphicsScene* scene = view->scene();


    // create a new line item
    QGraphicsLineItem* line;
    if(label.toString().toStdString() == "nav") {
        line = new NavEdgeLineItem(x1,y1,x2,y2);
    } else {
        line = new EdgeLineItem(x1,y1,x2,y2);
    }

    // set the pen color to the given color and thickness
    QPen pen(color, thickness);
    line->setPen(pen);
    line->setData(0, id);
    line->setData(1, label);
//    std::cout<<street_name.toString().toStdString()<<std::endl;
    line->setData(2, length);
    line->setData(3, street_name);
    line->setToolTip("Street name: " + street_name.toString() + "\nLength: " + QString::fromStdString(std::to_string(round(length.toDouble() * pow(10, 2)) / pow(10, 2))) + " meters");
    // Add the line item to the scene
    scene->addItem(line);
}

void XHRDraw::updateView(QGraphicsView* view) {
    view->update();
}


// TODO: remove scaling from first draw of graph
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

        int _id = verts[i].getId();
//        std::cout<<_id<<endl;
        // draw vertex
        XHRDraw::drawVertexWithData(graphicsView, scaledX, scaledY, 0.2, Qt::red, QVariant(_id));
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

void XHRDraw::drawGraph(QGraphicsView* graphicsView, QString fileName, int viewWidth, int viewHeight, Graph graph, ProgressBar* progressBarWindow, bool streetData) {
    int progress = 0;

    std::vector<std::vector<double>> lines;

    // compute scale factors
    double scaleX = viewWidth / (graph.getMaxX() - graph.getMinX());
    double scaleY = viewHeight / (graph.getMaxY() - graph.getMinY());

    auto verts = graph.getVertices();
    auto edges = graph.getEdges();

    // iterate edges only
#pragma omp parallel for
    for (int i = 0; i < edges.size() ; i++) {
        auto edge = edges.at(i);

        int source_vid = edge.getSourceVid();
        int dest_vid = edge.getDestVid();

        auto source_vertex = graph.getVertexById(source_vid);
        auto dest_vertex = graph.getVertexById(dest_vid);

        double scaledX1 = std::round((source_vertex.getX() - graph.getMinX()) * scaleX);
        double scaledY1 = std::round((source_vertex.getY() - graph.getMinY()) * scaleY);
        double scaledX2 = std::round((dest_vertex.getX() - graph.getMinX()) * scaleX);
        double scaledY2 = std::round((dest_vertex.getY() - graph.getMinY()) * scaleY);

        // prevent weird edges bug by calculating distance between points.. idk why this bug happens?
        if(std::sqrt(std::pow(scaledX2 - scaledX1, 2) + std::pow(scaledY2 - scaledY1, 2)) > 0) {
            XHRDraw::drawEdgeWithData(graphicsView, scaledX1, scaledY1, scaledX2, scaledY2, Qt::black, 0.2, QVariant(source_vid), QString("") ,QString::fromStdString(edge.getName()), QVariant(edge.getLength()));
        }
    }

    // iterate through the vertices of the graph and add them to the scene
#pragma omp parallel for
    for (int i = 0; i < verts.size(); ++i) {
        // scale to screen size
        double scaledX = std::round((verts[i].getX() - graph.getMinX()) * scaleX );
        double scaledY = std::round((verts[i].getY() - graph.getMinY()) * scaleY );

        int _id = verts[i].getId();
//        std::cout<<_id<<endl;
        // draw vertex
        XHRDraw::drawVertexWithData(graphicsView, scaledX, scaledY, 0.2, Qt::red, QVariant(_id));
    }

    // fit all into view
    graphicsView->fitInView(graphicsView->scene()->itemsBoundingRect());
}

void XHRDraw::drawNavPath(QGraphicsView* g, std::vector<Vertex> v, Graph graph_n, int viewWidth, int viewHeight) {

    // compute scale factors
    double scaleX = viewWidth / (graph_n.getMaxX() - graph_n.getMinX());
    double scaleY = viewHeight / (graph_n.getMaxY() - graph_n.getMinY());

    auto verts = graph_n.getVertices();
    auto edges = graph_n.getEdges();

    auto v_size =  v.size();

#pragma omp parallel for
    for (int i = 1; i < v_size; ++i) {
        // scale to screen size
        double scaledX1 = std::round((v[i-1].getX() - graph_n.getMinX()) * scaleX );
        double scaledY1 = std::round((v[i-1].getY() - graph_n.getMinY()) * scaleY );
        double scaledX2 = std::round((v[i].getX() - graph_n.getMinX()) * scaleX );
        double scaledY2 = std::round((v[i].getY() - graph_n.getMinY()) * scaleY );

        int _id = v[i-1].getId();
    //        std::cout<<_id<<endl;
        // draw vertex
        XHRDraw::drawVertexWithData(g, scaledX1, scaledY1, 0.5, Qt::green, QVariant(_id), QVariant("nav"));

        // find edge data?
        auto source_vid = v[i-1].getId();
        auto end_vid = v[i].getId();
        auto it = std::find_if(edges.begin(), edges.end(), [source_vid, end_vid](const Edge& e) {
            return e.getSourceVid() == source_vid && e.getDestVid() == end_vid;
        });

        Edge edge;

        if (it != edges.end()) {
            edge = *it;
        } else {
            std::cout<<"Something went wrong... why is there no edge here? --- drawNavPath, edges"<<std::endl;
        }
        // draw the edge to the next vertex
        XHRDraw::drawEdgeWithData(g, scaledX1, scaledY1, scaledX2, scaledY2, Qt::green, 0.5, QVariant(source_vid), QString::fromStdString("nav"),QString::fromStdString(edge.getName()), QVariant(edge.getLength()));
    }
    // add last vertex
    double scaledX1 = std::round((v[v_size].getX() - graph_n.getMinX()) * scaleX );
    double scaledY1 = std::round((v[v_size].getY() - graph_n.getMinY()) * scaleY );

    int _id = v[v_size].getId();

    XHRDraw::drawVertexWithData(g, scaledX1, scaledY1, 0.5, Qt::green, QVariant(_id), QVariant("nav"));
}

void XHRDraw::drawNavPathVisited(QGraphicsView* g, std::vector<Vertex> v, Graph graph_n, int viewWidth, int viewHeight) {

    // compute scale factors
    double scaleX = viewWidth / (graph_n.getMaxX() - graph_n.getMinX());
    double scaleY = viewHeight / (graph_n.getMaxY() - graph_n.getMinY());

    auto v_size =  v.size();

#pragma omp parallel for
    for (int i = 0; i < v_size; ++i) {
        // scale to screen size
        double scaledX = std::round((v[i].getX() - graph_n.getMinX()) * scaleX );
        double scaledY = std::round((v[i].getY() - graph_n.getMinY()) * scaleY );

        int _id = v[i].getId();
    //        std::cout<<_id<<endl;
        // draw vertex
        XHRDraw::drawVertexWithData(g, scaledX, scaledY, 0.5, Qt::darkBlue, QVariant(_id), QVariant("nav"));

    }
}

void XHRDraw::clearItems(QGraphicsView* view) {
    // clear the scene
    view->scene()->clear();
    // reset any transformations
    view->resetTransform();
    // release any cached items -> can cause crashes
    view->resetCachedContent();
}

void XHRDraw::clearItems(QGraphicsView* view, std::string label) {
    QGraphicsScene* scene = view->scene();

    // could instead save a vector of pointers to the vertices and erase that way... way more efficient
    for (auto item : scene->items()) {
        if (item->data(1).toString().toStdString() == label) {
            scene->removeItem(item);
        }
    }
}
