#ifndef GAME_ENGINE_MAINWINDOW_H
#define GAME_ENGINE_MAINWINDOW_H

#include "SceneWindow.h"
#include <QSurfaceFormat>
#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QMainWindow>
#include <QVBoxLayout>
#include <iostream>

class MainWindow : public QMainWindow
{
public:
    MainWindow(QWidget *parent = nullptr)
    {
        setWindowTitle("Bipki Engine");
        resize(1800, 1000); // Устанавливаем размер главного окна

        _sceneWindow = new Window(this);
        setCentralWidget(_sceneWindow);


    }

    ~MainWindow() override
    {
        delete _sceneWindow; // Уничтожаем объект сцены при закрытии окна
    }

private:
    Window *_sceneWindow; // Указатель на объект окна сцены
};

#endif //GAME_ENGINE_MAINWINDOW_H
