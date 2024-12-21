#ifndef GAME_ENGINE_SHADER_H
#define GAME_ENGINE_SHADER_H

#include <QOpenGLFunctions>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QOpenGLShaderProgram>
#include <QOpenGLContext>
#include <unordered_map>
#include <stdexcept>
#include <QMatrix4x4>
#include <QVector3D>
#include <iostream>

class Shader : protected QOpenGLFunctions {
public:
    explicit Shader(const QString &vertPath, const QString &fragPath)
    {
        initializeOpenGLFunctions();

        // Чтение шейдерных файлов
        QString vertexSource = readFile(vertPath);
        QString fragmentSource = readFile(fragPath);

        // Скомпилировать вершинный шейдер
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        compileShader(vertexShader, vertexSource);

        // Скомпилировать фрагментный шейдер
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        compileShader(fragmentShader, fragmentSource);

        // Создание программы
        handle = glCreateProgram();
        glAttachShader(handle, vertexShader);
        glAttachShader(handle, fragmentShader);
        linkProgram(handle);

        // Очистка ненужных шейдеров
        glDetachShader(handle, vertexShader);
        glDetachShader(handle, fragmentShader);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // Заполнение карты uniform-ов
        glGetProgramiv(handle, GL_ACTIVE_UNIFORMS, &numberOfUniforms);

        for (int i = 0; i < numberOfUniforms; i++) {
            char name[256];
            GLsizei length;
            glGetActiveUniform(handle, i, 256, &length, nullptr, nullptr, name);
            int location = glGetUniformLocation(handle, name);
            uniformLocations[name] = location;
        }
    }

    ~Shader() {
        glDeleteProgram(handle); // Удаляем программу шейдеров
    }

    void use() {
        glUseProgram(handle); // Активируем шейдер
    }

    void setInt(const QString &name, int data) {
        use();
        glUniform1i(uniformLocations.at(name.toStdString()), data);
    }

    void setFloat(const QString &name, float data) {
        use();
        glUniform1f(uniformLocations.at(name.toStdString()), data);
    }

    void setMatrix4(const QString &name, const QMatrix4x4 &data) {
        use();
        glUniformMatrix4fv(uniformLocations.at(name.toStdString()), 1, GL_FALSE, data.constData());
    }

    void setVector3(const QString &name, const QVector3D &data) {
        use();
        glUniform3f(uniformLocations.at(name.toStdString()), data.x(), data.y(), data.z());
    }

private:
    GLuint handle; // Дескриптор ID программы
    int numberOfUniforms; // Число юниформов
    std::unordered_map<std::string, GLint> uniformLocations; // Карта юниформ-локаторов

    QString readFile(const QString &path) {
        QFile file(path);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            throw std::runtime_error(("Failed to open file: " + path).toStdString());
        }
        QTextStream stream(&file);
        return stream.readAll();
    }

    void compileShader(GLuint shader, const QString &source) {
        QByteArray byteArray = source.toUtf8();
        const char *cStr = byteArray.constData();

        glShaderSource(shader, 1, &cStr, nullptr);
        glCompileShader(shader);

        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success) {
            char log[512];
            glGetShaderInfoLog(shader, 512, nullptr, log);
            throw std::runtime_error(QString("Error compiling shader: %1").arg(log).toStdString());
        }
    }

    void linkProgram(GLuint program) {
        glLinkProgram(program);

        GLint success;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            char log[512];
            glGetProgramInfoLog(program, 512, nullptr, log);
            throw std::runtime_error(QString("Error linking program: %1").arg(log).toStdString());
        }
    }
};
#endif //GAME_ENGINE_SHADER_H
