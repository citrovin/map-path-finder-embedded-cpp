#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

            // Perform the zoom in operation centered on the mouse click position
            graphicsView->scale(1.2, 1.2);
            graphicsView->centerOn(point);
        }
        if (mouseEvent->button() == Qt::RightButton)
        {
            // Get the position of the mouse click relative to the graphics view
            QPointF point = graphicsView->mapToScene(mouseEvent->pos());

            // Perform the zoom in operation centered on the mouse click position
            graphicsView->scale(0.8, 0.8);
            graphicsView->centerOn(point);
        }
    }
    return QMainWindow::eventFilter(obj, event);
}


