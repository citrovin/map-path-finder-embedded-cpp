#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QGraphicsItem>

#include "src/headers/graph.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool eventFilter(QObject *obj, QEvent *event);
    void selectTool(std::string);
    std::string getTool();
    Graph graph;

private slots:
    void on_load_graph_button_released();

    void on_clear_screen_button_released();

    void on_tool_zoom_button_released();

    void on_tool_select_button_released();

private:
    Ui::MainWindow *ui;
    std::string tool = "select";
    int selectedVertID;
    QGraphicsEllipseItem* selectedVertItem = nullptr;
};
#endif // MAINWINDOW_H
