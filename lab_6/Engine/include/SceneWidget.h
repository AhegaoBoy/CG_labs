#ifndef LAB_6_SCENEWIDGET_H
#define LAB_6_SCENEWIDGET_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QTimer>
#include <vector>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QMatrix4x4>
#include <QMenu>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>



#include "Camera.h"


class scene_widget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT



private:
    QOpenGLShaderProgram shaderProgram;   // Шейдерная программа
    QOpenGLShaderProgram lightShaderProgram;
    QOpenGLVertexArrayObject VAO;        // VAO (Vertex Array Object)
    QOpenGLBuffer VBO;
    QOpenGLVertexArrayObject lightVAO;
    QOpenGLBuffer lightVBO;
    QOpenGLVertexArrayObject cubeVAO;
    QOpenGLBuffer cubeVBO;
    QOpenGLVertexArrayObject paleVAO;
    QOpenGLBuffer paleVBO;

private:
    bool leftMousePressed = false;   // Состояние ЛКМ (для вращения камеры)
    bool rightMousePressed = false; // Состояние ПКМ (для перемещения объектов)

    QVector2D lastMousePosition;    // Последнее положение мыши (для камеры и объектов)
    int selectedObjectIndex = -1;  // Индекс выбранного объекта (если выбран)

    // Меню для управления объектами:
    QMenu* objectMenu = nullptr;
private:
    QVector3D cameraPosition;
    QVector3D cameraFront;
    QVector3D cameraUp;

    QMatrix4x4 projectionMatrix;
    QMatrix4x4 viewMatrix;

    float cameraSpeed = 0.1f;

    float yaw = -90.0f;        // Угол поворота камеры (лево/право)
    float pitch = 0.0f;        // Угол наклона камеры (вверх/вниз)
    float fov = 45.0f;         // Поле зрения для зума

    bool firstMouse = true;    // Для обработки начального положения мыши
    float lastX;               // Последняя позиция по X
    float lastY;               // Последняя позиция по Y



public:
    explicit scene_widget(QWidget* parent = nullptr);
    ~scene_widget();
    enum object_type
    {
        cube,
        sphere,
        plane,
        light_source
    };

    void add_object(object_type type);
    void add_light(float x, float y, float z, QVector3D color, float intensity);

protected:
    void keyPressEvent(QKeyEvent* event) override;   // Обработка клавиш
    void mouseMoveEvent(QMouseEvent* event) override; // Обработка движения мыши
    void wheelEvent(QWheelEvent* event) override;   // Обработка колеса мыши
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void showObjectMenu(const QPoint& pos);
    int pickObject(QPoint const& mouse_pos);

protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;



private:
    class object
    {
        object_type type;
        float x, y, z;
        friend scene_widget;
        QVector3D color;
        float intensity;
    public:
        object(object_type type, float x, float y, float z, QVector3D color = QVector3D(1, 1, 1), float intensity = 1.0f) :
                                            type(type), x(x), y(y), z(z),
                                            color(color), intensity(intensity){};
    };
    std::vector<object> objects;
    QTimer* timer;

    bool rayIntersectsObject(const QVector3D& rayOrigin, const QVector3D& rayDir, const object& obj);
    QVector3D calculateRayDirection(const QPoint &mouse_pos);

};
#endif //LAB_6_SCENEWIDGET_H
