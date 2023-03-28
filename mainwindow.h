#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QGraphicsItem>
#include "qlcdnumber.h"

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
    void setStartVert(int id);
    void setEndVert(int id);
    int getStartVert();
    int getEndVert();

private slots:
    void on_clear_screen_button_released();

    void on_tool_zoom_button_released();

    void on_tool_select_button_released();

    void on_set_start_button_released();

    void on_set_end_button_released();

    void on_util_flip_vertical_released();

    void on_util_flip_horizontal_released();

    void on_horizontalSlider_valueChanged(int value);

    void on_tool_move_button_released();

    void on_util_reset_rotation_button_released();

    void on_util_reset_zoom_button_released();

    void on_load_graph_button_2_released();

    void on_algo_bfs_button_released();

    void on_algo_djikstra_button_released();

    void on_algo_astar_button_released();

    void on_clear_path_button_released();

private:
    Ui::MainWindow *ui;
    std::string tool = "select";
    int selectedVertID = -1;
    QGraphicsEllipseItem* selectedVertItem = nullptr;
    int startVertID = -1;
    int endVertID = -1;
    QPointF lastMousePos;
    double prevRotation = 0;
    bool graphDisplayed = false;
};
#endif // MAINWINDOW_H
