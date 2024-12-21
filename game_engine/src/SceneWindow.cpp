#include "SceneWindow.h"
#include <cmath>
#include <QMouseEvent>
#include <QString>

Window::Window(QWidget *parent) : QOpenGLWidget(parent), _lightingShader(nullptr), _lampShader(nullptr) {
    // Инициализация камеры
    _camera = new Camera(QVector3D(0.0f, 0.0f, 3.0f), 1.0f);

    // Таймер для обновлений
    _timer = new QTimer(this);
    connect(_timer, &QTimer::timeout, this, QOverload<>::of(&Window::update));
    _timer->start(16); // Около 60 FPS
}

Window::~Window() {
    delete _lightingShader;
    delete _lampShader;
    delete _diffuseTexture;
    delete _specularTexture;
}

void Window::initializeGL() {
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);

    setupShaders();
    setupTextures();
    setupDungeon();



    // Создаем и заполняем массивы вершин и текстур
    GLfloat vertices[] = {
            // Задняя грань
            -0.5f, -0.5f, -0.5f, // Нижний левый угол
            0.5f, -0.5f, -0.5f, // Нижний правый угол
            0.5f,  0.5f, -0.5f, // Верхний правый угол
            0.5f,  0.5f, -0.5f, // Верхний правый угол
            -0.5f,  0.5f, -0.5f, // Верхний левый угол
            -0.5f, -0.5f, -0.5f, // Нижний левый угол

            // Передняя грань
            -0.5f, -0.5f,  0.5f, // Нижний левый угол
            0.5f, -0.5f,  0.5f, // Нижний правый угол
            0.5f,  0.5f,  0.5f, // Верхний правый угол
            0.5f,  0.5f,  0.5f, // Верхний правый угол
            -0.5f,  0.5f,  0.5f, // Верхний левый угол
            -0.5f, -0.5f,  0.5f, // Нижний левый угол

            // Левая грань
            -0.5f,  0.5f,  0.5f, // Верхний правый угол
            -0.5f,  0.5f, -0.5f, // Верхний левый угол
            -0.5f, -0.5f, -0.5f, // Нижний левый угол
            -0.5f, -0.5f, -0.5f, // Нижний левый угол
            -0.5f, -0.5f,  0.5f, // Нижний правый угол
            -0.5f,  0.5f,  0.5f, // Верхний правый угол

            // Правая грань
            0.5f,  0.5f,  0.5f, // Верхний правый угол
            0.5f,  0.5f, -0.5f, // Верхний левый угол
            0.5f, -0.5f, -0.5f, // Нижний левый угол
            0.5f, -0.5f, -0.5f, // Нижний левый угол
            0.5f, -0.5f,  0.5f, // Нижний правый угол
            0.5f,  0.5f,  0.5f, // Верхний правый угол

            // Нижняя грань
            -0.5f, -0.5f, -0.5f, // Задний левый угол
            0.5f, -0.5f, -0.5f, // Задний правый угол
            0.5f, -0.5f,  0.5f, // Передний правый угол
            0.5f, -0.5f,  0.5f, // Передний правый угол
            -0.5f, -0.5f,  0.5f, // Передний левый угол
            -0.5f, -0.5f, -0.5f, // Задний левый угол

            // Верхняя грань
            -0.5f,  0.5f, -0.5f, // Задний левый угол
            0.5f,  0.5f, -0.5f, // Задний правый угол
            0.5f,  0.5f,  0.5f, // Передний правый угол
            0.5f,  0.5f,  0.5f, // Передний правый угол
            -0.5f,  0.5f,  0.5f, // Передний левый угол
            -0.5f,  0.5f, -0.5f  // Задний левый угол
    };

    GLfloat texCoords[] = {
            // Текстурные координаты для задней грани
            0.0f, 0.0f, // Нижний левый угол
            1.0f, 0.0f, // Нижний правый угол
            1.0f, 1.0f, // Верхний правый угол
            1.0f, 1.0f, // Верхний правый угол
            0.0f, 1.0f, // Верхний левый угол
            0.0f, 0.0f, // Нижний левый угол

            // Текстурные координаты для передней грани
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,

            // Текстурные координаты для левой грани
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,

            // Текстурные координаты для правой грани
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,

            // Текстурные координаты для нижней грани
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,

            // Текстурные координаты для верхней грани
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f
    };


    glGenBuffers(1, &_vboPositions);
    glBindBuffer(GL_ARRAY_BUFFER, _vboPositions);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &_vboTexCoords);
    glBindBuffer(GL_ARRAY_BUFFER, _vboTexCoords);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Сброс привязки
}

void Window::resizeGL(int w, int h) {
    glViewport(0, 0, w, h);
    _camera->setAspect((float)w / h);
}

void Window::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Используем шейдер освещения
    _lightingShader->use();
    _lightingShader->setMatrix4("view", _camera->GetViewMatrix());
    _lightingShader->setMatrix4("projection", _camera->GetProjectionMatrix());

    // Настраиваем освещённые материалы
    _lightingShader->setInt("material.diffuse", 0);
    _lightingShader->setInt("material.specular", 1);
    _lightingShader->setFloat("material.shininess", 32.0f);



    // Включаем позиции и текстурные координаты из буферов вручную
    glEnableVertexAttribArray(0); // Активируем атрибут для позиции вершин
    glBindBuffer(GL_ARRAY_BUFFER, _vboPositions);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr); // Указываем, как читать данные для позиции

    glEnableVertexAttribArray(1); // Текстурные координаты
    glBindBuffer(GL_ARRAY_BUFFER, _vboTexCoords);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr); // Указываем, как читать данные для текстур



    // Отрисовка каждого куба
    for (const auto &pos : _cubePositions) {
        QMatrix4x4 model;
        model.translate(pos);
        _lightingShader->setMatrix4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // Отключаем активные массивы
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0); // Отвязываем массивный буфер
}

void Window::setupShaders() {
    // Загрузка и компиляция шейдеров
    _lightingShader = new Shader("/mnt/a/mai_stuff/Computer_grafics/game_engine/Shaders/shader.vs", "/mnt/a/mai_stuff/Computer_grafics/game_engine/Shaders/lighting.fs");
    _lampShader = new Shader("/mnt/a/mai_stuff/Computer_grafics/game_engine/Shaders/shader.vs", "/mnt/a/mai_stuff/Computer_grafics/game_engine/Shaders/shader.fs");
}

void Window::setupTextures()
{
    Texture tex(1);
    _diffuseTexture = tex.loadFromFile("/mnt/a/mai_stuff/Computer_grafics/game_engine/Resources/floor.png");
    _specularTexture = tex.loadFromFile("/mnt/a/mai_stuff/Computer_grafics/game_engine/Resources/floor.png");
}

void Window::setupDungeon() {
    // Пример генерации объектов сцены
    _cubePositions.push_back(QVector3D(0.0f, -1.0f, 0.0f)); // Пол
    _cubePositions.push_back(QVector3D(1.0f, 0.0f, 0.0f));  // Стена
}

bool Window::checkPlayerCollision(const QVector3D &newPos) {
    for (const auto &pos : _cubePositions) {
        if ((newPos - pos).lengthSquared() < 0.25f) {
            return true;
        }
    }
    return false;
}

void Window::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_W:
            _camera->processKeyboard(Camera::FORWARD);
            break;
        case Qt::Key_S:
            _camera->processKeyboard(Camera::BACKWARD);
            break;
        case Qt::Key_A:
            _camera->processKeyboard(Camera::LEFT);
            break;
        case Qt::Key_D:
            _camera->processKeyboard(Camera::RIGHT);
            break;
    }
}

void Window::keyReleaseEvent(QKeyEvent *event)
{
    // Обработка отпускания клавиш (если требуется)
}

void Window::mouseMoveEvent(QMouseEvent *event) {
    auto pos = event->pos();

    if (_firstMouseMovement) {
        _lastMousePosition = static_cast<QVector2D>(pos);
        _firstMouseMovement = false;
    }

    int dx = pos.x() - _lastMousePosition.x();
    int dy = _lastMousePosition.y() - pos.y(); // Инвертируем Y

    _lastMousePosition = static_cast<QVector2D>(pos);

    _camera->processMouse(dx, dy);
}

void Window::wheelEvent(QWheelEvent *event) {
    _camera->processScroll(event->angleDelta().y() / 120.0f);
}