#include "MainWindow.h"
#include "SceneWidget.h"

main_window::main_window(QWidget* parent)
        : QMainWindow(parent), lastFrame(std::chrono::high_resolution_clock::now())

{
    resize(800, 600);


    scene = new scene_widget(this);
    setCentralWidget(scene);

    auto* add_cube_button = new QPushButton("Add cube", this);
    auto* add_sphere_button = new QPushButton("Add sphere", this);
    auto* add_light_button = new QPushButton("Add light", this);
    auto* add_pale = new QPushButton("Add pale", this);

    QToolBar* tool_bar = new QToolBar;
    addToolBar(Qt::LeftToolBarArea, tool_bar);
    tool_bar->addWidget(add_cube_button);
    tool_bar->addWidget(add_sphere_button);
    tool_bar->addWidget(add_light_button);
    tool_bar->addWidget(add_pale);
    connect(add_cube_button, &QPushButton::clicked, [=] { scene->add_object(scene_widget::cube); });
    connect(add_sphere_button, &QPushButton::clicked, [=]{ scene->add_object(scene_widget::sphere);});
    connect(add_pale, &QPushButton::clicked, [=]{scene->add_object(scene_widget::plane);});
    connect(add_light_button, &QPushButton::clicked, [=]{scene->add_light(0, 0, 4, {1, 1, 1}, 1);});

    scene->setFocus();
}


main_window::~main_window() = default;