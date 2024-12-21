#ifndef LAB_6_MAINWINDOW_H
#define LAB_6_MAINWINDOW_H
#include "SceneWidget.h"
#include <QMainWindow>
#include <QPushButton>
#include <QToolBar>

class main_window : public QMainWindow
{
Q_OBJECT

public:
    main_window(QWidget* parent);
    ~main_window();

private:
    scene_widget* scene; // Указатель на объект отрисовки сцены
    std::chrono::time_point<std::chrono::high_resolution_clock> lastFrame;



};

#endif //LAB_6_MAINWINDOW_H
