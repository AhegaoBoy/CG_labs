#ifndef LAB_6_CAMERA_H
#define LAB_6_CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <QKeyEvent>
#include <iostream>
class camera
{
private:

    glm::vec3 position;


    glm::vec3 front;


    glm::vec3 up;


    glm::vec3 right;


    glm::vec3 worldUp;


    float speed;
    float sensitivity;


    float pitch; // Угол поворота вверх/вниз (по оси X)
    float yaw;   // Угол поворота влево/вправо (по оси Y)

    // Увеличение/уменьшение масштаба (поле зрения)
    float zoom;

public:
    // Конструктор
    camera(glm::vec3 startPosition = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 startUp = glm::vec3(0.0f, 1.0f, 0.0f),
           float startYaw = -90.0f,
           float startPitch = 0.0f,
           float startSpeed = 2.5f,
           float startSensitivity = 0.1f,
           float startZoom = 45.0f)
            : position(startPosition), front(glm::vec3(0.0f, 0.0f, -1.0f)), up(startUp), worldUp(startUp), right(glm::vec3(1.0f, 0.0f, 0.0f)),
              yaw(startYaw), pitch(startPitch), speed(startSpeed), sensitivity(startSensitivity), zoom(startZoom)
    {
        updateCameraVectors(); // Обновление векторов камеры
    }

    // --- Методы ---
    // Получить видовую матрицу
    glm::mat4 getViewMatrix() const;

    // Перемещение камеры (вперёд, назад, влево, вправо)
    void moveCamera(int event, float deltaTime);


    // Обработка движения мыши для изменения углов поворота камеры
    void processMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);

    // Обработка событий колеса мыши для управления зумом
    void processMouseScroll(float yOffset);

    // Получить текущее значение зума
    float getZoom() const
    {
        return zoom;
    }

    // Получить текущую позицию камеры
    glm::vec3 getPosition() const
    {
        return position;
    }

private:
    // Обновление векторов направления камеры (на основе углов yaw и pitch)
    void updateCameraVectors();

};

#endif //LAB_6_CAMERA_H
