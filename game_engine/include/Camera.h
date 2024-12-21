#ifndef GAME_ENGINE_CAMERA_H
#define GAME_ENGINE_CAMERA_H
#include <QtMath>
#include <QMatrix4x4>
#include <QVector3D>
#include <algorithm>

class Camera {
private:
    QVector3D _front = QVector3D(0.0f, 0.0f, -1.0f);
    QVector3D _up = QVector3D(0.0f, 1.0f, 0.0f);
    QVector3D _right = QVector3D(1.0f, 0.0f, 0.0f);

    float _pitch = 0.0f;
    float _yaw = -90.0f;
    float _fov = 90.0f;

    float AspectRatio = 1.0f;
    float _movementSpeed = 2.5f;
    float deltaTime = 0.016f;
    void UpdateVectors() {
        float pitchRad = qDegreesToRadians(_pitch);
        float yawRad = qDegreesToRadians(_yaw);

        _front.setX(cos(pitchRad) * cos(yawRad));
        _front.setY(sin(pitchRad));
        _front.setZ(cos(pitchRad) * sin(yawRad));
        _front.normalize();

        _right = QVector3D::crossProduct(_front, QVector3D(0.0f, 1.0f, 0.0f)).normalized();
        _up = QVector3D::crossProduct(_right, _front).normalized();
    }

public:
    QVector3D Position;

    enum CameraMovement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    Camera(QVector3D position, float aspectRatio)
            : Position(position), AspectRatio(aspectRatio) {}

    QVector3D GetFront() const { return _front; }
    QVector3D GetUp() const { return _up; }
    QVector3D GetRight() const { return _right; }

    float GetPitch() const { return _pitch; }
    void SetPitch(float value) {
        _pitch = std::clamp(value, -89.0f, 89.0f);
        UpdateVectors();
    }

    float GetYaw() const { return _yaw; }
    void SetYaw(float value) {
        _yaw = value;
        UpdateVectors();
    }

    float GetFov() const { return _fov; }
    void SetFov(float value) {
        _fov = std::clamp(value, 1.0f, 90.0f);
    }

    QMatrix4x4 GetViewMatrix() const {
        QMatrix4x4 view;
        view.lookAt(Position, Position + _front, _up);
        return view;
    }

    QMatrix4x4 GetProjectionMatrix() const {
        QMatrix4x4 projection;
        projection.perspective(_fov, AspectRatio, 0.01f, 100.0f);
        return projection;
    }

    void setAspect(float aspect) {
        AspectRatio = aspect;
    }

    void processKeyboard(CameraMovement direction) {
        float velocity = _movementSpeed * deltaTime;

        if (direction == FORWARD) Position += _front * velocity;
        if (direction == BACKWARD) Position -= _front * velocity;
        if (direction == LEFT) Position -= _right * velocity;
        if (direction == RIGHT) Position += _right * velocity;
    }

    void setMovementSpeed(float speed) {
        _movementSpeed = std::max(0.0f, speed);
    }

    float getMovementSpeed() const {
        return _movementSpeed;
    }

    // Обработка движения мыши
    void processMouse(float xOffset, float yOffset, bool constrainPitch = true) {
        const float sensitivity = 0.1f;
        xOffset *= sensitivity;
        yOffset *= sensitivity;

        _yaw += xOffset;
        _pitch += yOffset;

        if (constrainPitch) _pitch = std::clamp(_pitch, -89.0f, 89.0f);

        UpdateVectors();
    }

    // Обработка прокрутки колеса
    void processScroll(float yOffset) {
        const float zoomSensitivity = 1.0f;
        _fov -= yOffset * zoomSensitivity;
        _fov = std::clamp(_fov, 1.0f, 90.0f);
    }
};

#endif //GAME_ENGINE_CAMERA_H