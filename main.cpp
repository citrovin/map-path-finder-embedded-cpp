#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QMessageBox>
#include <QTextEdit>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QPainter>
#include <QVBoxLayout>
#include <QLabel>

#include "src/headers/graph.hpp" // graph.h
#include "mainwindow.h"
#include "xhrdraw.h"

//void showMessage(QList<QString> messages, int index = 0) {
//    QMessageBox::StandardButton reply;
//    reply = QMessageBox::information(nullptr, "Message", messages[index], QMessageBox::Ok);
//    if (reply == QMessageBox::Ok && index + 1 < messages.size()) {
//        showMessage(messages, index + 1);
//    }
//}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    // Get the graphicsview container define in UI
    QGraphicsView* graphicsView = mainWindow.findChild<QGraphicsView*>("graphicsView");

    int viewWidth = graphicsView->width();
    int viewHeight = graphicsView->height();

    if (graphicsView == nullptr) {
        // Could not find the graphicsView object in the mainwindow.ui file
        return 0;
    }

    // DEBUG --------- DISPLAY LOADED FILE

    // create a file dialog to select the file to read
    // TODO: ENABLE IN FINAL VERSION
//    QString fileName = QFileDialog::getOpenFileName(nullptr, "Open File", QDir::currentPath());

    QString fileName = "D:\\Projects\\SA\\EC++\\map-path-finder-embedded-cpp\\data\\graph_dc_area.2022-03-11.txt";
//    QString fileName = "D:\\Projects\\SA\\EC++\\map-path-finder-embedded-cpp\\data\\test_data.txt";
    // open the file
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // error opening the file
        QMessageBox::warning(nullptr, "Error", "Could not open file");
        return 0;
    } else {
        QMessageBox::information(nullptr, "Success", "Data file opened");
    }

    // create a QTextEdit widget
    QTextEdit *textEdit = new QTextEdit();

    // set the text of the widget
    textEdit->setPlainText("Hello, world!");

    // show the widget
    textEdit->show();

    // read the file contents and set them to the QTextEdit widget
    QTextStream in(&file);
    QString text = in.readAll();
    textEdit->setPlainText(text);

    // close the file
    file.close();

    // create a Graph object
    Graph graph(fileName.toStdString());
//    Graph graph("data/graph_dc_area.2022-03-11.txt");

    // compute scale factors
    double scaleX = viewWidth / (graph.getMaxX() - graph.getMinX());
    double scaleY = viewHeight / (graph.getMaxY() - graph.getMinY());
    
    // iterate through the vertices and edges of the graph and add them to the scene
    for (auto& vertex : graph.getVertices()) {
        // scale to screen size
        double scaledX = (vertex.getX() - graph.getMinX()) * scaleX;
        double scaledY = (vertex.getY() - graph.getMinY()) * scaleY;

        // draw vertex
        XHRDraw::drawCircle(graphicsView, scaledX, scaledY, 1, Qt::red);

        // iterate through the adjacency list of the vertex and add edges to the scene
        for (auto& adjacent_vertex_id : vertex.getAdjacencyList()) {

            // get coords
            auto adjacent_vertex = graph.getVertexById(adjacent_vertex_id);

            // scale to screen size
            double scaledX2 = (adjacent_vertex.getX() - graph.getMinX()) * scaleX;
            double scaledY2 = (adjacent_vertex.getY() - graph.getMinY()) * scaleY;

            //draw lines
            XHRDraw::drawLine(graphicsView,scaledX,scaledY,scaledX2,scaledY2,Qt::yellow,1);
        }
    }

//    XHRDraw::drawCircle(graphicsView, 250, 250, 30, QColor::fromRgbF(1,1,1,1));
//    XHRDraw::drawCircle(graphicsView, 150, 150, 90, QColor::fromRgbF(1,1,1,1));
    
    mainWindow.show();
    return app.exec();
}
