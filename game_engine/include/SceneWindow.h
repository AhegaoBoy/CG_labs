#ifndef GAME_ENGINE_SCENEWINDOW_H
#define GAME_ENGINE_SCENEWINDOW_H
#pragma once

#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>
#include <QVector2D>
#include <QVector3D>
#include <QMatrix4x4>
#include <QKeyEvent>
#include <vector>
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"

class Window : public QOpenGLWidget, protected QOpenGLFunctions {
Q_OBJECT
private:
    GLuint _vboPositions;
    GLuint _vboTexCoords;
public:
    explicit Window(QWidget *parent = nullptr);
    ~Window();

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

private:
    // Методы для инициализации объектов сцены
    void setupShaders();
    void setupTextures();
    void setupDungeon();

    // Проверка столкновений камеры со стенами
    bool checkPlayerCollision(const QVector3D& newPos);

    // Буферы и шейдеры
    GLuint _vaoModel, _vaoLamp, _vbo;
    Shader *_lightingShader;
    Shader *_lampShader;

    // Текстуры
    Texture *_diffuseTexture;
    Texture *_specularTexture;

    // Камера
    Camera *_camera;
    QVector2D _lastMousePosition;
    bool _firstMouseMovement = true;

    // Позиции объектов в мире
    std::vector<QVector3D> _cubePositions;
    std::vector<QVector3D> _enemies;
    std::vector<QVector3D> _bulletPositions;
    QVector3D _pointLights[4]; // Пример для точечных источников света

    // Счётчик врагов
    int _enemyKillCount = 0;

    // Управление
    QTimer *_timer; // Таймер для вызова обновления
};
#endif //GAME_ENGINE_SCENEWINDOW_H
