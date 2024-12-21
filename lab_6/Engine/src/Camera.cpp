#include "Camera.h"
#include <QDebug>
void camera::moveCamera(int key, float deltaTime)
{
    float velocity = speed * deltaTime;          // Debug вывод:
    std::cout << "Position before: " << position.x << ", " << position.y << ", " << position.z << "\n";
    std::cout << "Front: " << front.x << ", " << front.y << ", " << front.z << "\n";
    std::cout << "Right: " << right.x << ", " << right.y << ", " << right.z << "\n";
    std::cout << "Velocity: " << velocity << "\n";

    if (key == Qt::Key_W)
        position += front * velocity;
    if (key == Qt::Key_S)
        position -= front * velocity;
    if (key == Qt::Key_A)
        position -= right * velocity;
    if (key == Qt::Key_D)
        position += right * velocity;

    // Итоговая позиция
    std::cout << "Position after: " << position.x << ", " << position.y << ", " << position.z << "\n";
}

void camera::processMouseMovement(float xOffset, float yOffset, bool constrainPitch)
{
    xOffset *= sensitivity;
    yOffset *= sensitivity;

    yaw += xOffset;   // Поворот камеры влево/вправо
    pitch += yOffset; // Поворот камеры вверх/вниз

    // Ограничиваем угол поворота камеры вверх/вниз (чтобы избежать артефактов)
    if (constrainPitch)
    {
        if (pitch > 89.0f)
            pitch = 89.0f;

        if (pitch < -89.0f)
            pitch = -89.0f;
    }

    // Обновляем вектора камеры
    updateCameraVectors();
}

void camera::processMouseScroll(float yOffset)
{
    zoom -= yOffset;
    if (zoom < 1.0f)
        zoom = 1.0f;

    if (zoom > 45.0f)
        zoom = 45.0f;
}

glm::mat4 camera::getViewMatrix() const

{
    return glm::lookAt(position, position + front, up);
}

void camera::updateCameraVectors()
{
    // Обновляем фронт (вектор перед камерой)
    glm::vec3 newFront;
    newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    newFront.y = sin(glm::radians(pitch));
    newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(newFront);

    // Обновляем правый и верхний векторы
    right = glm::normalize(glm::cross(front, worldUp)); // Правый вектор
    up = glm::normalize(glm::cross(right, front));      // Верхний вектор
}