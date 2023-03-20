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
#include "src/headers/display.h" // display.h
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

    if (graphicsView == nullptr) {
        // Could not find the graphicsView object in the mainwindow.ui file
        return 0;
    }

    // DEBUG --------- DISPLAY LOADED FILE



//    XHRDraw::drawCircle(graphicsView, 250, 250, 30, QColor::fromRgbF(1,1,1,1));
//    XHRDraw::drawCircle(graphicsView, 150, 150, 90, QColor::fromRgbF(1,1,1,1));
    
    XHRDraw::updateView(graphicsView);
    mainWindow.show();
    return app.exec();
}
