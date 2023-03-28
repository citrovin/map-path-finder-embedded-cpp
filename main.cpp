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

#include "mainwindow.h"
#include "xhrdraw.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;

    // show the main window
    mainWindow.show();

    // get the graphicsview container define in UI
    QGraphicsView* graphicsView = mainWindow.findChild<QGraphicsView*>("graphicsView");

    // if for some reason the graphicsview didn't load
    if (graphicsView == nullptr) {
        return 0;
    }

    // update the graphics view in case we didn't
    XHRDraw::updateView(graphicsView);

    // show the main window
    mainWindow.show();
    return app.exec();
}
