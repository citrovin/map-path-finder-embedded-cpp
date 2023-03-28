#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <QElapsedTimer>
#include <QFileDialog>
#include <QTextEdit>

#include "progressbar.h"
#include "xhrdraw.h"
#include "messagebox.h"
#include "src/headers/display.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Get the graphics view from the UI
    QGraphicsView* graphicsView = ui->graphicsView;

    // Set up the scene and add it to the graphics view
    QGraphicsScene* scene = new QGraphicsScene(this);
    graphicsView->setScene(scene);

    // Center the graphics view on the scene
    graphicsView->setAlignment(Qt::AlignCenter);

    // Install event filter on the graphics view
    graphicsView->viewport()->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Implement the event filter in the main window
bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    // Get the graphics view from the UI
    QGraphicsView* graphicsView = ui->graphicsView;

    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
        if(getTool() == "zoom") {
            if (mouseEvent->button() == Qt::LeftButton)
            {
                QPointF viewCenter = graphicsView->viewport()->rect().center();
                // Get the position of the mouse click relative to the graphics view
                QPointF point = graphicsView->mapToScene(mouseEvent->pos());

                QTransform transform = graphicsView->transform(); // current view transform
                qreal zoom = qMax(transform.m11(), transform.m22()); // get the zoom factor

                // adjust the scene position based on the zoom factor
//                point = viewCenter + (point - viewCenter) / zoom;

                // Perform the zoom in operation centered on the mouse click position
                graphicsView->centerOn(point);
                graphicsView->scale(1.2, 1.2);


                // adjust the size of all shapes based on the new zoom level
//                qreal newScale = qMax(transform.m11(), transform.m22());
//                foreach (QGraphicsItem *item, graphicsView->scene()->items()) {
//                    item->setScale(item->scale() * newScale / zoom);
//                }
            }
            if (mouseEvent->button() == Qt::RightButton)
            {
                QPointF viewCenter = graphicsView->viewport()->rect().center();
                // get the position of the mouse click relative to the graphics view
                QPointF point = graphicsView->mapToScene(mouseEvent->pos());

                QTransform transform = graphicsView->transform(); // current view transform
                qreal zoom = qMax(transform.m11(), transform.m22()); // get the zoom factor

                // adjust the scene position based on the zoom factor
//                point = viewCenter + (point - viewCenter) / zoom;

                // zoom in centered on the mouse click position
                graphicsView->centerOn(point);
                graphicsView->scale(0.8, 0.8);

                // adjust the size of all shapes based on the new zoom level
//                qreal newScale = qMax(transform.m11(), transform.m22());
//                foreach (QGraphicsItem *item, graphicsView->scene()->items()) {
//                    item->setScale(item->scale() * newScale / zoom);
//                }
            }
        } else if (getTool() == "select"){
            if (mouseEvent->button() == Qt::LeftButton)
            {
                // get the position of the mouse click relative to the graphics view
                QPointF point = graphicsView->mapToScene(mouseEvent->pos());

                QTransform transform = graphicsView->transform(); // current view transform
                qreal zoom = qMax(transform.m11(), transform.m22()); // get the zoom factor

                // adjust the scene position based on the zoom factor
//                point.setX(point.x() / zoom);
//                point.setY(point.y() / zoom);


//                std::cout<<"Click at: "<<point.x()<< " " <<point.y()<<std::endl;

                // Iterate through all items in the scene to find the closest point
                QGraphicsItem* closestItem = nullptr;
                qreal minDistance = std::numeric_limits<qreal>::max();

//                std::cout<<"Min dist.: "<<minDistance<<std::endl;

                foreach (QGraphicsItem* item, graphicsView->scene()->items()) {
                    // Check if the item is selectable and visible
                    if (item->flags() & QGraphicsItem::ItemIsSelectable && item->isVisible()) {
                        // Get the center point of the item
                        QPointF center = item->boundingRect().center();

                        // Compute the distance from the center to the mouse position
                        qreal distance = QLineF(center, point).length();

//                        std::cout<<"Dist. to closest: "<<distance<<std::endl;

                        // If the distance is smaller than the current minimum, update the closest item and distance
                        if (distance < minDistance) {
//                            std::cout<<"Found closest point with dist.: "<< distance <<std::endl;
                            closestItem = item;
                            minDistance = distance;
                        }
                    }
                }

                if(closestItem != nullptr) {
                    selectedVertID = closestItem->data(0).toInt();

                    // set color as selected vert
                    if (closestItem && closestItem->type() == QGraphicsEllipseItem::Type) {
                        QGraphicsEllipseItem* ellipseItem = qgraphicsitem_cast<QGraphicsEllipseItem*>(closestItem);
                        ellipseItem->setBrush(QBrush(Qt::blue));
                        ellipseItem->setPen(QPen(Qt::blue));
                        ellipseItem->setSelected(true);
                        ellipseItem->setAcceptHoverEvents(false);

                        // reset color of previous selected vert
                        if(selectedVertItem != nullptr) {
                            selectedVertItem->setBrush(QBrush(Qt::red));
                            selectedVertItem->setPen(QPen(Qt::red));
                            selectedVertItem->setSelected(false);
                            ellipseItem->setAcceptHoverEvents(true);
                        }

                        // assign new active item
                        selectedVertItem = qgraphicsitem_cast<QGraphicsEllipseItem*>(closestItem);
                    }

                    // update ui
                    ui->lcd_selected_id->setDigitCount(6);
                    ui->lcd_selected_id->display(selectedVertID);
                    ui->lcd_selected_x->display(graph.getVertexById(selectedVertID).getX()/1000);
                    ui->lcd_selected_y->display(graph.getVertexById(selectedVertID).getY()/1000);
                }
            }

//            std::cout<<selectedVertID<<std::endl;
        } else if( getTool() == "move") {
            if (mouseEvent->button() == Qt::LeftButton) {

            }
        }

        if(getTool() != "move") {
            graphicsView->setDragMode(QGraphicsView::NoDrag);
        } else {
           graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
        }
    }

    if (event->type() == QEvent::MouseMove){
        QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);

        if( getTool() == "move") {
            if (mouseEvent->buttons() & Qt::LeftButton) {

            }
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::on_clear_screen_button_released()
{
    // remove any refs to items
    selectedVertID = -1;
    selectedVertItem = nullptr;

    // get the first QGraphicsView object in the widget
    QGraphicsView* graphicsView = ui->graphicsView;

    // clear the scene
    XHRDraw::clearItems(graphicsView);

    graphicsView->resetTransform();

    // reset graph display check
    graphDisplayed = false;
}

void MainWindow::selectTool(std::string t) {
    tool = t;
}

std::string MainWindow::getTool() {
    return tool;
}


void MainWindow::on_tool_zoom_button_released()
{
    selectTool("zoom");
}


void MainWindow::on_tool_select_button_released()
{
    selectTool("select");
}


void MainWindow::on_set_start_button_released()
{
    if(selectedVertID != -1) {
        ui->lcd_start_id->setDigitCount(6);
        ui->lcd_start_id->display(selectedVertID);
        // update ui
        ui->lcd_start_x->display(graph.getVertexById(selectedVertID).getX()/1000);
        ui->lcd_start_y->display(graph.getVertexById(selectedVertID).getY()/1000);
        setStartVert(selectedVertID);
    } else {
        QMessageBox::warning(this, "Warning!", "Please select a vertex first.");
    }
}


void MainWindow::on_set_end_button_released()
{
    if(selectedVertID != -1) {
        ui->lcd_end_id->setDigitCount(6);
        ui->lcd_end_id->display(selectedVertID);
        // update ui
        ui->lcd_end_x->display(graph.getVertexById(selectedVertID).getX()/1000);
        ui->lcd_end_y->display(graph.getVertexById(selectedVertID).getY()/1000);
        setEndVert(selectedVertID);
    } else {
        QMessageBox::warning(this, "Warning!", "Please select a vertex first.");
    }
}

void MainWindow::setEndVert(int id) {
    endVertID = id;
}

int MainWindow::getEndVert() {
    return endVertID;
}

void MainWindow::setStartVert(int id) {
    startVertID = id;
}

int MainWindow::getStartVert() {
    return startVertID;
}

void MainWindow::on_util_flip_vertical_released()
{
    QGraphicsView* graphicsView = ui->graphicsView;
    // flip the viewport vertically
    graphicsView->setTransform(QTransform(1, 0, 0, -1, 0, 0));
}


void MainWindow::on_util_flip_horizontal_released()
{
    QGraphicsView* graphicsView = ui->graphicsView;
    // flip the viewport horizontally
    graphicsView->setTransform(QTransform(-1, 0, 0, 1, 0, 0));
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    // rotate the view
    QGraphicsView* graphicsView = ui->graphicsView;
    // set delta rotation
    graphicsView->setTransform(graphicsView->transform().rotate(prevRotation - value));
    // set last angle as this one
    prevRotation = value;
}


void MainWindow::on_tool_move_button_released()
{
    selectTool("move");
}


void MainWindow::on_util_reset_rotation_button_released()
{
    // get view
    QGraphicsView* graphicsView = ui->graphicsView;
    // rotate with negative of last rotation to get to 0 rotation
    graphicsView->setTransform(graphicsView->transform().rotate(-360+prevRotation));
    // set last angle as 0
    prevRotation = 0;
    // reset slider
    ui->horizontalSlider->setSliderPosition(0);
}


void MainWindow::on_util_reset_zoom_button_released()
{
    QGraphicsView* graphicsView = ui->graphicsView;
    QTransform transform;
    transform.reset();
//    transform.rotate(ui->horizontalSlider->sliderPosition());
    graphicsView->setTransform(transform);

    // reset slider
    ui->horizontalSlider->setSliderPosition(0);
}

bool MainWindow::checkFileHeader(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file " << filename << std::endl;
        return false;
    }
    std::string line;
    getline(file, line);
    if (line != "# Vertex List") {
        std::cerr << "Invalid file header in " << filename << std::endl;
        return false;
    }
    getline(file, line);
    if (line != "# V,vertexid,longitude,latitude,x*,y*") {
        std::cerr << "Invalid file header in " << filename << std::endl;
        return false;
    }
    return true;
}


void MainWindow::on_load_graph_button_2_released()
{
    if(graphDisplayed == false) {
        // Get the graphics view from the UI
        QGraphicsView* graphicsView = ui->graphicsView;

        graphicsView->setToolTipDuration(1000);

        // get bounds
        int viewWidth = graphicsView->width();
        int viewHeight = graphicsView->height();

    //    XHRDraw::drawCircle(graphicsView,150, 150, 50, Qt::blue);

        QString fileName = QFileDialog::getOpenFileName(nullptr, "Open File", QDir::currentPath());

        // Timing
        QElapsedTimer timer;
        timer.start();
    //        QString fileName = "D:\\Projects\\SA\\EC++\\map-path-finder-embedded-cpp\\data\\graph_dc_area.2022-03-11.txt";
    //        QString fileName = "D:\\Projects\\SA\\EC++\\map-path-finder-embedded-cpp\\data\\test_data.txt";
    //    QString fileName = "D:\\Projects\\SA\\EC++\\map-path-finder-embedded-cpp\\data\\display.txt";
        // open the file
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            // error opening the file
            QMessageBox::warning(this, "Error", "Could not open file");
        } else {
            std::string f = fileName.toStdString();
            if(checkFileHeader(f)) {
                QMessageBox::information(this, "Success", "Data file opened");


                // create a Graph object
            //    Graph graph = loadGraph(fileName.toStdString());
                Graph g(fileName.toStdString());
                g.computeMercator();

                graph = g;

                // TODO: implement threads and mutex for the progressbar display...
                // Create the progress bar window
                int progress_max = graph.getVertices().size() + graph.getEdges().size();
                ProgressBar progressBarWindow(nullptr, progress_max);

                // Show the progress bar window
            //    progressBarWindow.show();

                // start loading graph
                // draw with street data ~ 27x slower
                XHRDraw::drawGraph(graphicsView,fileName,viewWidth, viewHeight, graph, &progressBarWindow,true);

                // Hide the progress bar window when the operation is complete
            //    progressBarWindow.hide();

                // Code to be timed
                std::cout << "Elapsed time:" << timer.elapsed() << "milliseconds" << std::endl;
                QString str = "Elapsed time: " + QString::number(timer.elapsed()/1000.0) + " seconds";
                MessageBox::show("Elapsed time", str);

                file.close();

                // set graph display check
                graphDisplayed = true;
            } else {
                QMessageBox::warning(this, "Warning!", "Invalid file contents.");
            }
        }
    } else {
        QMessageBox::warning(this, "Warning!", "There is already an active graph in the scene.");
    }
}


void MainWindow::on_algo_bfs_button_released()
{
    if(startVertID != -1 && endVertID != -1){
        QGraphicsView* graphicsView = ui->graphicsView;
        // clear previous
        XHRDraw::clearItems(graphicsView,"nav");
        // get bounds
        int viewWidth = graphicsView->width();
        int viewHeight = graphicsView->height();
        std::vector<Vertex> nav_path = graph.bfs(startVertID,endVertID).first;
        std::vector<Vertex> nav_path_visited = graph.bfs(startVertID,endVertID).second;
        XHRDraw::drawNavPathVisited(graphicsView,nav_path_visited,graph,viewWidth,viewHeight);
        XHRDraw::drawNavPath(graphicsView,nav_path,graph,viewWidth,viewHeight);

        // set lcds for vertices visited and path length
        ui->algo_distance_lcd->setDigitCount(6);
        ui->algo_distance_lcd->display((int)nav_path.size());
        ui->algo_visited_lcd->setDigitCount(6);
        ui->algo_visited_lcd->display((int)nav_path_visited.size());
    } else {
        QMessageBox::warning(this, "Warning!", "You must select a start and end point first.");
    }
}


void MainWindow::on_algo_djikstra_button_released()
{
    if(startVertID != -1 && endVertID != -1){
        QGraphicsView* graphicsView = ui->graphicsView;
        // clear previous
        XHRDraw::clearItems(graphicsView,"nav");
        // get bounds
        int viewWidth = graphicsView->width();
        int viewHeight = graphicsView->height();
        std::vector<Vertex> nav_path = graph.dijkstra(startVertID,endVertID).first;
        std::vector<Vertex> nav_path_visited = graph.dijkstra(startVertID,endVertID).second;
        XHRDraw::drawNavPathVisited(graphicsView,nav_path_visited,graph,viewWidth,viewHeight);
        XHRDraw::drawNavPath(graphicsView,nav_path,graph,viewWidth,viewHeight);

        // set lcds for vertices visited and path length
        ui->algo_distance_lcd->setDigitCount(6);
        ui->algo_distance_lcd->display((int)nav_path.size());
        ui->algo_visited_lcd->setDigitCount(6);
        ui->algo_visited_lcd->display((int)nav_path_visited.size());
    } else {
        QMessageBox::warning(this, "Warning!", "You must select a start and end point first.");
    }
}

void MainWindow::on_algo_astar_button_released()
{
    if(startVertID != -1 && endVertID != -1){
        QGraphicsView* graphicsView = ui->graphicsView;
        // clear previous
        XHRDraw::clearItems(graphicsView,"nav");
        // get bounds
        int viewWidth = graphicsView->width();
        int viewHeight = graphicsView->height();
        std::vector<Vertex> nav_path = graph.astar(startVertID,endVertID).first;
        std::vector<Vertex> nav_path_visited = graph.astar(startVertID,endVertID).second;
        XHRDraw::drawNavPathVisited(graphicsView,nav_path_visited,graph,viewWidth,viewHeight);
        XHRDraw::drawNavPath(graphicsView,nav_path,graph,viewWidth,viewHeight);

        // set lcds for vertices visited and path length
        ui->algo_distance_lcd->setDigitCount(6);
        ui->algo_distance_lcd->display((int)nav_path.size());
        ui->algo_visited_lcd->setDigitCount(6);
        ui->algo_visited_lcd->display((int)nav_path_visited.size());
    } else {
        QMessageBox::warning(this, "Warning!", "You must select a start and end point first.");
    }
}

void MainWindow::on_clear_path_button_released()
{
    QGraphicsView* graphicsView = ui->graphicsView;

    XHRDraw::clearItems(graphicsView,"nav");

    // reset lcds
    ui->algo_distance_lcd->setDigitCount(6);
    ui->algo_distance_lcd->display(0);
    ui->algo_visited_lcd->setDigitCount(6);
    ui->algo_visited_lcd->display(0);
}

