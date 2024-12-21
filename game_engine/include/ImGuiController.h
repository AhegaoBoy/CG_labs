#ifndef GAME_ENGINE_IMGUICONTROLLER_H
#define GAME_ENGINE_IMGUICONTROLLER_H
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <imgui.h>
#include <imgui_impl_qt.h>
#include <imgui_impl_opengl3.h>
#include <iostream>

class ImGuiController : protected QOpenGLFunctions {
public:
    ImGuiController(int width, int height)
            : _windowWidth(width), _windowHeight(height) {
        initializeOpenGLFunctions();
        initializeImGui();
    }

    void initializeImGui() {
        // Инициализация ImGui
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO &io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Поддержка клавиш

        ImGui::StyleColorsDark(); // Тема
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    void createDeviceResources() {
        // создаем ресурсы GPU
        _vao.create();
        _vao.bind();

        _vertexBuffer.create();
        _vertexBuffer.bind();
        _vertexBuffer.allocate(sizeof(GLfloat) * MAX_VERTEX_BUFFER_SIZE);

        _indexBuffer.create();
        _indexBuffer.bind();
        _indexBuffer.allocate(sizeof(GLushort) * MAX_INDEX_BUFFER_SIZE);

        // Создаем шейдеры
        _shaderProgram = new QOpenGLShaderProgram();
        _shaderProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
        _shaderProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
        if (!_shaderProgram->link()) {
            std::cerr << "Failed to link shader program: " << _shaderProgram->log().toStdString() << std::endl;
        }
    }

    void renderFrame() {
        // Здесь выполняется рендер
        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        drawGui();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void drawGui() {
        // Рисуем элементы интерфейса
        ImGui::Begin("Hello, world!"); // Создаем окно
        ImGui::Text("This is a text"); // Простой текст
        ImGui::End();
    }

    void cleanup() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
    }

private:
    int _windowWidth;
    int _windowHeight;

    QOpenGLVertexArrayObject _vao;
    QOpenGLBuffer _vertexBuffer;
    QOpenGLBuffer _indexBuffer;

    QOpenGLShaderProgram *_shaderProgram = nullptr;

    const int MAX_VERTEX_BUFFER_SIZE = 10000;
    const int MAX_INDEX_BUFFER_SIZE = 2000;

    const char *vertexShaderSource = R"(
        #version 330 core
        layout(location = 0) in vec2 position;
        layout(location = 1) in vec2 texCoord;
        layout(location = 2) in vec4 color;

        uniform mat4 projection;

        out vec2 v_texCoord;
        out vec4 v_color;

        void main() {
            gl_Position = projection * vec4(position, 0.0, 1.0);
            v_texCoord = texCoord;
            v_color = color;
        }
    )";

    const char *fragmentShaderSource = R"(
        #version 330 core
        in vec2 v_texCoord;
        in vec4 v_color;

        out vec4 fragColor;

        uniform sampler2D fontTexture;

        void main() {
            fragColor = v_color * texture(fontTexture, v_texCoord);
        }
    )";
};
#endif //GAME_ENGINE_IMGUICONTROLLER_H
