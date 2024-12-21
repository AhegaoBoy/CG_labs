#ifndef GAME_ENGINE_TEXTURE_H
#define GAME_ENGINE_TEXTURE_H
#include <QOpenGLFunctions>
#include <QImage>
#include <QString>
#include <QDebug>
#include <stdexcept>

class Texture : protected QOpenGLFunctions
        {
public:
    GLuint handle;

    // Конструктор для создания текстуры из OpenGL-дескриптора.
    explicit Texture(GLuint glHandle)
            : handle(glHandle) {
        initializeOpenGLFunctions(); // Инициализация OpenGL функций
    }

    // Загружает текстуру из файла.
    Texture* loadFromFile(const QString& path) {
        initializeOpenGLFunctions(); // Ensure OpenGL functions are initialized

        GLuint textureHandle;
        glGenTextures(1, &textureHandle);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureHandle);

        // Загружаем изображение с помощью QImage
        QImage image(path);
        if (image.isNull()) {
            throw std::runtime_error("Failed to load texture: " + path.toStdString());
        }
    }
};
#endif //GAME_ENGINE_TEXTURE_H
