#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QMessageBox>
#include <QElapsedTimer>

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
        if (mouseEvent->button() == Qt::LeftButton)
        {
            // Get the position of the mouse click relative to the graphics view
            QPointF point = graphicsView->mapToScene(mouseEvent->pos());

            // get zoom
            qreal currentScale = graphicsView->transform().m11();

            // Perform the zoom in operation centered on the mouse click position
            graphicsView->scale(1.2, 1.2);
            graphicsView->centerOn(point);

            // Adjust the size of all shapes based on the new zoom level
            qreal newScale = graphicsView->transform().m11();
            foreach (QGraphicsItem *item, graphicsView->scene()->items()) {
                item->setScale(item->scale() * newScale / currentScale);
            }
        }
        if (mouseEvent->button() == Qt::RightButton)
        {
            // Get the position of the mouse click relative to the graphics view
            QPointF point = graphicsView->mapToScene(mouseEvent->pos());

            // get zoom
            qreal currentScale = graphicsView->transform().m11();

            // Perform the zoom in operation centered on the mouse click position
            graphicsView->scale(0.8, 0.8);
            graphicsView->centerOn(point);

            // Adjust the size of all shapes based on the new zoom level
            qreal newScale = graphicsView->transform().m11();
            foreach (QGraphicsItem *item, graphicsView->scene()->items()) {
                item->setScale(item->scale() * newScale / currentScale);
            }
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::on_load_graph_button_released()
{
    // Timing
    QElapsedTimer timer;
    timer.start();

    // Get the graphics view from the UI
    QGraphicsView* graphicsView = ui->graphicsView;

    // get bounds
    int viewWidth = graphicsView->width();
    int viewHeight = graphicsView->height();

//    XHRDraw::drawCircle(graphicsView,150, 150, 50, Qt::blue);

//        QString fileName = "D:\\Projects\\SA\\EC++\\map-path-finder-embedded-cpp\\data\\graph_dc_area.2022-03-11.txt";
//        QString fileName = "D:\\Projects\\SA\\EC++\\map-path-finder-embedded-cpp\\data\\test_data.txt";
    QString fileName = "D:\\Projects\\SA\\EC++\\map-path-finder-embedded-cpp\\data\\display.txt";
    // open the file
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // error opening the file
        QMessageBox::warning(nullptr, "Error", "Could not open file");
    } else {
        QMessageBox::information(nullptr, "Success", "Data file opened");
    }

    // create a Graph object
    Graph graph = loadGraph(fileName.toStdString());
//    Graph graph(fileName.toStdString());
//    graph.computeMercator();
    int progress_max = graph.getVertices().size() + graph.getEdges().size();

    // Create the progress bar window
    ProgressBar progressBarWindow(nullptr, progress_max);

    // Show the progress bar window
    progressBarWindow.show();

    // start loading graph
    XHRDraw::drawGraph(graphicsView,fileName,viewWidth, viewHeight, graph, &progressBarWindow);

    // Hide the progress bar window when the operation is complete
    progressBarWindow.hide();

    // Code to be timed
    std::cout << "Elapsed time:" << timer.elapsed() << "milliseconds" << std::endl;
    QString str = "Elapsed time: " + QString::number(timer.elapsed()/1000.0) + " seconds";
    MessageBox::show("Elapsed time", str);
}

