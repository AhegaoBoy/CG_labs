#include "SceneWidget.h"

scene_widget::scene_widget(QWidget *parent) :
        QOpenGLWidget(parent),
        VBO(QOpenGLBuffer::VertexBuffer),  // Указываем, что буфер - это Vertex Buffer
        cameraPosition(0.0f, 0.0f, 3.0f),
        cameraFront(0.0f, 0.0f, -1.0f),
        cameraUp(0.0f, 1.0f, 0.0f),
        fov(45.0f)
{
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&scene_widget::update));
    timer->start(16);

    setCursor(Qt::BlankCursor);
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

scene_widget::~scene_widget()
{
    makeCurrent();
    VAO.destroy();  // Уничтожаем VAO
    VBO.destroy();  // Уничтожаем VBO
    doneCurrent();
    delete timer;
}

void scene_widget::initializeGL() {
    initializeOpenGLFunctions();

    // Установка фона
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glEnable(GL_DEPTH_TEST);  // Включаем буфер глубины

    // Компиляция шейдера
    if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "/mnt/a/mai_stuff/Computer_grafics/lab_6/Engine/shaders/vertex_shader.vs")) {
        qDebug() << "Vertex shader compilation failed:" << shaderProgram.log();
    }

    if (!shaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "/mnt/a/mai_stuff/Computer_grafics/lab_6/Engine/shaders/fragment_shader.fs")) {
        qDebug() << "Fragment shader compilation failed:" << shaderProgram.log();
    }

    if (!shaderProgram.link()) {
        qDebug() << "Shader program linking failed:" << shaderProgram.log();
    }

    if (!lightShaderProgram.addShaderFromSourceFile(QOpenGLShader::Vertex, "/mnt/a/mai_stuff/Computer_grafics/lab_6/Engine/shaders/light_vertex_shaders.vs")) {
        qDebug() << "Light vertex shader compilation failed:" << lightShaderProgram.log();
    }

    if (!lightShaderProgram.addShaderFromSourceFile(QOpenGLShader::Fragment, "/mnt/a/mai_stuff/Computer_grafics/lab_6/Engine/shaders/light_fragment_shader.fs")) {
        qDebug() << "Light fragment shader compilation failed:" << lightShaderProgram.log();
    }

    if (!lightShaderProgram.link()) {
        qDebug() << "Light shader program linking failed:" << lightShaderProgram.log();
    }
    // === Создаём данные для отрисовки ===
    GLfloat vertices[] = {
            // Позиции       // Цвета
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // Левая вершина
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // Правая вершина
            0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // Верхняя вершина
    };

    // Генерируем VAO
    VAO.create();
    VAO.bind();

    // Генерируем VBO
    VBO.create();
    VBO.bind();
    VBO.allocate(vertices, sizeof(vertices));

    // Настраиваем атрибуты вершин
    shaderProgram.bind();
    shaderProgram.enableAttributeArray("position");
    shaderProgram.setAttributeBuffer("position", GL_FLOAT, 0, 3, 6 * sizeof(GLfloat));

    shaderProgram.enableAttributeArray("color");
    shaderProgram.setAttributeBuffer("color", GL_FLOAT, 3 * sizeof(GLfloat), 3, 6 * sizeof(GLfloat));

    VAO.release();
    shaderProgram.release();

    // Создаём VBO и VAO для источника света
    GLfloat lightVertices[] = {
            // Позиции куба (без цветов и нормалей)
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f
    };

    lightVAO.create();  // Создаем VAO для источника света
    lightVAO.bind();

    lightVBO.create();
    lightVBO.bind();
    lightVBO.allocate(lightVertices, sizeof(lightVertices));

    lightShaderProgram.enableAttributeArray(0);
    lightShaderProgram.setAttributeBuffer(0, GL_FLOAT, 0, 3, 3 * sizeof(float));

    lightVAO.release();
}

void scene_widget::resizeGL(int w, int h)
{
    float aspectRatio = static_cast<float>(w) / static_cast<float>(h);
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(fov, aspectRatio, 0.1f, 100.0f);
}

void scene_widget::paintGL()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    viewMatrix.setToIdentity();
    viewMatrix.lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

    // Используем шейдер
    shaderProgram.bind();

    shaderProgram.setUniformValue("view", viewMatrix);
    shaderProgram.setUniformValue("projection", projectionMatrix);

    VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);  // Рисуем треугольник
    VAO.release();

    shaderProgram.release();    viewMatrix.setToIdentity();
    viewMatrix.lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

    // Используем шейдер
    shaderProgram.bind();

    shaderProgram.setUniformValue("view", viewMatrix);
    shaderProgram.setUniformValue("projection", projectionMatrix);

    VAO.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);  // Рисуем треугольник
    VAO.release();

    shaderProgram.release();

    for (auto object: objects) {
        QMatrix4x4 model;
        model.translate(object.x, object.y, object.z);

        QMatrix4x4 model_view_matrix = viewMatrix * model;

        shaderProgram.bind();  // Привязываем шейдерную программу
        shaderProgram.setUniformValue("model", model);
        shaderProgram.setUniformValue("view", viewMatrix);
        shaderProgram.setUniformValue("projection", projectionMatrix);

        switch (object.type) {
            case cube: {
                QOpenGLBuffer cubeVAO;
                GLfloat cubeVertices[] = {
                        // Позиции           // Нормали         // Цвета (RGB)
                        // Передняя грань
                        -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f,  0.0f,  0.0f,
                        0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f,  0.0f,  0.0f,
                        0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f,  0.0f,  0.0f,
                        0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f,  0.0f,  0.0f,
                        -0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f,  0.0f,  0.0f,
                        -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f,  0.0f,  0.0f,

                        // Задняя грань
                        -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f,  1.0f,  0.0f,
                        -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f,  1.0f,  0.0f,
                        0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f,  1.0f,  0.0f,
                        0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f,  1.0f,  0.0f,
                        0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f,  1.0f,  0.0f,
                        -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f,  1.0f,  0.0f,

                        // Левая грань
                        -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f,  0.0f,  1.0f,
                        -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f,  0.0f,  1.0f,
                        -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f,  0.0f,  1.0f,
                        -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f,  0.0f,  1.0f,
                        -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f,  0.0f,  1.0f,
                        -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f,  0.0f,  1.0f,

                        // Правая грань
                        0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f,  1.0f,  0.0f,
                        0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f,  1.0f,  0.0f,
                        0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f,  1.0f,  0.0f,
                        0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f,  1.0f,  0.0f,
                        0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f,  1.0f,  0.0f,
                        0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f,  1.0f,  0.0f,

                        // Верхняя грань
                        -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f,  1.0f,  1.0f,
                        -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.0f,  1.0f,  1.0f,
                        0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.0f,  1.0f,  1.0f,
                        0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.0f,  1.0f,  1.0f,
                        0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f,  1.0f,  1.0f,
                        -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f,  1.0f,  1.0f,

                        // Нижняя грань
                        -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   1.0f,  0.0f,  1.0f,
                        0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f,  0.0f,  1.0f,
                        -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f,  0.0f,  1.0f,
                        0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f,  0.0f,  1.0f,
                        -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   1.0f,  0.0f,  1.0f,
                        0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   1.0f,  0.0f,  1.0f
                };

// Создание VAO и VBO для куба
                cubeVAO.create();
                cubeVAO.bind();

                QOpenGLBuffer cubeVBO(QOpenGLBuffer::VertexBuffer);
                cubeVBO.create();
                cubeVBO.bind();
                cubeVBO.allocate(cubeVertices, sizeof(cubeVertices));

// Устанавливаем атрибуты вершин
                shaderProgram.enableAttributeArray("position");
                shaderProgram.setAttributeBuffer("position", GL_FLOAT, 0, 3, 9 * sizeof(GLfloat));

                shaderProgram.enableAttributeArray("normal");
                shaderProgram.setAttributeBuffer("normal", GL_FLOAT, 3 * sizeof(GLfloat), 3, 9 * sizeof(GLfloat));

                shaderProgram.enableAttributeArray("color");
                shaderProgram.setAttributeBuffer("color", GL_FLOAT, 6 * sizeof(GLfloat), 3, 9 * sizeof(GLfloat));

                cubeVAO.release();

                cubeVAO.bind();
                glDrawArrays(GL_TRIANGLES, 0, 36);  // 36 вершин для куба (12 треугольников)
                cubeVAO.release();
                break;
            }
            case sphere:
            {
                QOpenGLBuffer sphereVAO;
                std::vector<float> sphereVertices;
                std::vector<unsigned int> sphereIndices;
                const int latitudeSegments = 32, longitudeSegments = 32;
                const float radius = 0.5f;

                for (int lat = 0; lat <= latitudeSegments; ++lat) {
                    for (int lon = 0; lon <= longitudeSegments; ++lon) {
                        float theta = lat * M_PI / latitudeSegments;
                        float phi = lon * 2 * M_PI / longitudeSegments;

                        float x = radius * sin(theta) * cos(phi);
                        float y = radius * cos(theta);
                        float z = radius * sin(theta) * sin(phi);

                        sphereVertices.push_back(x);
                        sphereVertices.push_back(y);
                        sphereVertices.push_back(z);

                        // Нормали
                        sphereVertices.push_back(x / radius);
                        sphereVertices.push_back(y / radius);
                        sphereVertices.push_back(z / radius);

                        // Цвет
                        sphereVertices.push_back(0.0f);
                        sphereVertices.push_back(0.0f);
                        sphereVertices.push_back(1.0f);
                    }
                }

// Индексы для треугольников
                for (int lat = 0; lat < latitudeSegments; ++lat) {
                    for (int lon = 0; lon < longitudeSegments; ++lon) {
                        int cur = lat * (longitudeSegments + 1) + lon;
                        int next = (lat + 1) * (longitudeSegments + 1) + lon;

                        sphereIndices.push_back(cur);
                        sphereIndices.push_back(next);
                        sphereIndices.push_back(cur + 1);

                        sphereIndices.push_back(next);
                        sphereIndices.push_back(next + 1);
                        sphereIndices.push_back(cur + 1);
                    }
                }

// Создание VAO, VBO и EBO для сферы
                sphereVAO.create();
                sphereVAO.bind();

                QOpenGLBuffer sphereVBO(QOpenGLBuffer::VertexBuffer);
                sphereVBO.create();
                sphereVBO.bind();
                sphereVBO.allocate(sphereVertices.data(), sphereVertices.size() * sizeof(float));

                QOpenGLBuffer sphereEBO(QOpenGLBuffer::IndexBuffer);
                sphereEBO.create();
                sphereEBO.bind();
                sphereEBO.allocate(sphereIndices.data(), sphereIndices.size() * sizeof(unsigned int));

// Установка атрибутов
                shaderProgram.enableAttributeArray("position");
                shaderProgram.setAttributeBuffer("position", GL_FLOAT, 0, 3, 9 * sizeof(float));

                shaderProgram.enableAttributeArray("normal");
                shaderProgram.setAttributeBuffer("normal", GL_FLOAT, 3 * sizeof(float), 3, 9 * sizeof(float));

                shaderProgram.enableAttributeArray("color");
                shaderProgram.setAttributeBuffer("color", GL_FLOAT, 6 * sizeof(float), 3, 9 * sizeof(float));

                sphereVAO.release();
                sphereVAO.bind();
                glDrawElements(GL_TRIANGLES, sphereIndices.size(), GL_UNSIGNED_INT, nullptr);  // Используем индексированный рендеринг
                sphereVAO.release();
                break;
            }

            case plane: {
                QOpenGLBuffer planeVAO;
                GLfloat planeVertices[] = {
                        // Позиции           // Нормали         // Цвета
                        -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // Левый нижний
                        1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // Правый нижний
                        -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // Левый верхний
                        1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f   // Правый верхний
                };

// Создание VAO и VBO для плоскости
                planeVAO.create();
                planeVAO.bind();

                QOpenGLBuffer planeVBO(QOpenGLBuffer::VertexBuffer);
                planeVBO.create();
                planeVBO.bind();
                planeVBO.allocate(planeVertices, sizeof(planeVertices));

                shaderProgram.enableAttributeArray("position");
                shaderProgram.setAttributeBuffer("position", GL_FLOAT, 0, 3, 9 * sizeof(GLfloat));

                shaderProgram.enableAttributeArray("normal");
                shaderProgram.setAttributeBuffer("normal", GL_FLOAT, 3 * sizeof(GLfloat), 3, 9 * sizeof(GLfloat));

                shaderProgram.enableAttributeArray("color");
                shaderProgram.setAttributeBuffer("color", GL_FLOAT, 6 * sizeof(GLfloat), 3, 9 * sizeof(GLfloat));

                planeVAO.release();

                planeVAO.bind();
                glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);  // Плоскость рендерится четырьмя вершинами через GL_TRIANGLE_STRIP
                planeVAO.release();
                break;
            }
            case light_source:
                QMatrix4x4 lightModelMatrix;
                lightModelMatrix.translate(object.x, object.y, object.z);
                lightModelMatrix.scale(0.2f);  // Указываем маленький размер для источника света

                lightShaderProgram.bind();  // Используем отдельный шейдер для света
                lightShaderProgram.setUniformValue("view", viewMatrix);
                lightShaderProgram.setUniformValue("projection", projectionMatrix);
                lightShaderProgram.setUniformValue("model", lightModelMatrix);


                GLfloat lightVertices[] = {
                        // Передняя грань
                        -0.5f, -0.5f,  0.5f,  // Левая нижняя вершина
                        0.5f, -0.5f,  0.5f,  // Правая нижняя вершина
                        0.5f,  0.5f,  0.5f,  // Правая верхняя вершина
                        0.5f,  0.5f,  0.5f,  // Правая верхняя вершина
                        -0.5f,  0.5f,  0.5f,  // Левая верхняя вершина
                        -0.5f, -0.5f,  0.5f,  // Левая нижняя вершина

                        // Задняя грань
                        -0.5f, -0.5f, -0.5f,  // Левая нижняя вершина
                        -0.5f,  0.5f, -0.5f,  // Левая верхняя вершина
                        0.5f,  0.5f, -0.5f,  // Правая верхняя вершина
                        0.5f,  0.5f, -0.5f,  // Правая верхняя вершина
                        0.5f, -0.5f, -0.5f,  // Правая нижняя вершина
                        -0.5f, -0.5f, -0.5f,  // Левая нижняя вершина

                        // Левая грань
                        -0.5f,  0.5f,  0.5f,  // Левая верхняя вершина
                        -0.5f,  0.5f, -0.5f,  // Левая верхняя вершина
                        -0.5f, -0.5f, -0.5f,  // Левая нижняя вершина
                        -0.5f, -0.5f, -0.5f,  // Левая нижняя вершина
                        -0.5f, -0.5f,  0.5f,  // Левая нижняя вершина
                        -0.5f,  0.5f,  0.5f,  // Левая верхняя вершина

                        // Правая грань
                        0.5f,  0.5f,  0.5f,  // Правая верхняя вершина
                        0.5f, -0.5f, -0.5f,  // Правая нижняя вершина
                        0.5f,  0.5f, -0.5f,  // Правая верхняя вершина
                        0.5f, -0.5f, -0.5f,  // Правая нижняя вершина
                        0.5f,  0.5f,  0.5f,  // Правая верхняя вершина
                        0.5f, -0.5f,  0.5f,  // Правая нижняя вершина

                        // Верхняя грань
                        -0.5f,  0.5f, -0.5f,  // Левый верхний
                        -0.5f,  0.5f,  0.5f,  // Левый верхний
                        0.5f,  0.5f,  0.5f,  // Правый верхний
                        0.5f,  0.5f,  0.5f,  // Правый верхний
                        0.5f,  0.5f, -0.5f,  // Правый верхний
                        -0.5f,  0.5f, -0.5f,  // Левый верхний

                        // Нижняя грань
                        -0.5f, -0.5f, -0.5f,  // Левый нижний
                        0.5f, -0.5f,  0.5f,  // Правый нижний
                        -0.5f, -0.5f,  0.5f,  // Левый нижний
                        0.5f, -0.5f,  0.5f,  // Правый нижний
                        -0.5f, -0.5f, -0.5f,  // Левый нижний
                        0.5f, -0.5f, -0.5f   // Правый нижний
                };

                lightVBO.bind();
                lightVBO.allocate(lightVertices, sizeof(lightVertices));

                lightShaderProgram.enableAttributeArray(0);
                lightShaderProgram.setAttributeBuffer(0, GL_FLOAT, 0, 3, 3 * sizeof(float));

                lightVAO.release();

                lightVAO.bind();  // Используем VAO, допустим, маленький куб.
                glDrawArrays(GL_TRIANGLES, 0, 36);
                lightShaderProgram.release();
                }
        }
}

void scene_widget::keyPressEvent(QKeyEvent* event)
{
    std::cout<<"Pressed " << event->key() << std::endl;

    if (event->key() == Qt::Key_W)
        cameraPosition += cameraSpeed * cameraFront;
    if (event->key() == Qt::Key_S)
        cameraPosition -= cameraSpeed * cameraFront;
    if (event->key() == Qt::Key_A)
        cameraPosition -= QVector3D::crossProduct(cameraFront, cameraUp).normalized() * cameraSpeed;
    if (event->key() == Qt::Key_D)
        cameraPosition += QVector3D::crossProduct(cameraFront, cameraUp).normalized() * cameraSpeed;

    std::cout << "Camera position: " << cameraPosition.x() << ", "
              << cameraPosition.y() << ", " << cameraPosition.z() << std::endl;

    update();
}

// Обработка событий движения мыши
void scene_widget::mouseMoveEvent(QMouseEvent* event)
{
    if (leftMousePressed)
    {
        // Вращение камеры
        QVector2D mouseDelta = QVector2D(event->pos()) - lastMousePosition; // Изменение положения мыши
        lastMousePosition = static_cast<QVector2D>(event->position());

        const float sensitivity = 0.2f;
        yaw += mouseDelta.x() * sensitivity;
        pitch -= mouseDelta.y() * sensitivity;

        // Ограничиваем угол pitch
        if (pitch > 89.0f) pitch = 89.0f;
        if (pitch < -89.0f) pitch = -89.0f;

        // Обновляем направление камеры
        QVector3D front;
        front.setX(cos(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));
        front.setY(sin(qDegreesToRadians(pitch)));
        front.setZ(sin(qDegreesToRadians(yaw)) * cos(qDegreesToRadians(pitch)));
        cameraFront = front.normalized();

        update();
    } else if (rightMousePressed && selectedObjectIndex != -1) {
        // Перемещение объекта
        QVector2D mouseDelta = QVector2D(event->pos()) - lastMousePosition; // Изменение положения мыши
        lastMousePosition = static_cast<QVector2D>(event->pos());

        // Обновляем положение выбранного объекта
        objects[selectedObjectIndex].x += mouseDelta.x() * 0.01f; // Масштаб движения мыши
        objects[selectedObjectIndex].y -= mouseDelta.y() * 0.01f; // Инвертируем Y для правильного движения

        update();
    }
}

// Обработка событий колеса мыши
void scene_widget::wheelEvent(QWheelEvent* event)
{
    fov -= event->angleDelta().y() / 120.0f; // Уменьшаем/увеличиваем FOV
    if (fov < 1.0f)
        fov = 1.0f; // Минимальный зум
    if (fov > 45.0f)
        fov = 45.0f; // Максимальный зум

    // Пересчитываем перспективу
    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(fov, float(width()) / float(height()), 0.1f, 100.0f);

    update(); // Обновляем сцену
}

void scene_widget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        leftMousePressed = true;    // Включаем вращение камеры
        lastMousePosition = static_cast<QVector2D>(event->pos()); // Сохраняем положение мыши
    } else if (event->button() == Qt::RightButton) {
        rightMousePressed = true;    // Включаем взаимодействие с объектами
        lastMousePosition = static_cast<QVector2D>(event->pos());


        // Находим объект под курсором (проверка пересечения)
        selectedObjectIndex = pickObject(event->pos()); // Реализуем функцию pickObject

        if (selectedObjectIndex != -1) {
            // Если объект найден, показываем меню для изменения параметров объекта
            showObjectMenu(event->pos());
        }
    }
}

void scene_widget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        leftMousePressed = false;  // Останавливаем вращение камеры
    }
    else if (event->button() == Qt::RightButton)
    {
        rightMousePressed = false; // Останавливаем взаимодействие с объектами
    }
}

void scene_widget::add_object(scene_widget::object_type type)
{
    object obj = { type, float(rand() % 10 - 5), float(rand() % 10 - 5), float(rand() % 10 - 5) };
    objects.push_back(obj);
    update();
}

void scene_widget::add_light(float x, float y, float z, QVector3D color, float intensity)
{
    std::cout<<"light"<<std::endl;
    object light = {light_source, x, y, z, color, intensity};
    objects.push_back(light);
    update();
}

void scene_widget::showObjectMenu(const QPoint& pos)
{
    if (selectedObjectIndex == -1) return; // Если объект не найден, меню не отображается

    // Создаем меню
    if (!objectMenu) {
        objectMenu = new QMenu(this);

        QAction* changeColorAction = new QAction("Change Color", this);
        QAction* deleteObjectAction = new QAction("Delete Object", this);

        objectMenu->addAction(changeColorAction);
        objectMenu->addAction(deleteObjectAction);

        connect(changeColorAction, &QAction::triggered, [this]() {
            // Пример: смена цвета объекта
            qDebug() << "Change color for object " << selectedObjectIndex;
        });
        connect(deleteObjectAction, &QAction::triggered, [this]() {
            // Удаление объекта
            if (selectedObjectIndex >= 0 && selectedObjectIndex < objects.size()) {
                objects.erase(objects.begin() + selectedObjectIndex);
                update();
            }
        });
    }

    objectMenu->exec(mapToGlobal(pos));
}

int scene_widget::pickObject(const QPoint &mouse_pos)
{


    QVector3D rayOrigin = cameraPosition;
    QVector3D rayDir = calculateRayDirection(mouse_pos);

    for (int i = 0; i < objects.size(); ++i) {
        if (rayIntersectsObject(rayOrigin, rayDir, objects[i])) {
            return i; // Луч пересёк объект
        }
    }
    return -1; // Луч никуда не попал
}

bool scene_widget::rayIntersectsObject(const QVector3D& rayOrigin, const QVector3D& rayDir, const object& obj)
{
    if (obj.type == sphere) {
        QVector3D center(obj.x, obj.y, obj.z);
        float t0, t1;
        QVector3D L = center - rayOrigin;
        float tca = QVector3D::dotProduct(L, rayDir);
        float d2 = QVector3D::dotProduct(L, L) - tca * tca;
        float radius2 = 0.5f * 0.5f; // Радиус сферы
        if (d2 > radius2) return false;
        float thc = sqrt(radius2 - d2);
        t0 = tca - thc;
        t1 = tca + thc;
        return (t0 > 0 || t1 > 0);
    }
    if (obj.type == cube) {
        QVector3D minBounds = QVector3D(obj.x - 0.5f, obj.y - 0.5f, obj.z - 0.5f);
        QVector3D maxBounds = QVector3D(obj.x + 0.5f, obj.y + 0.5f, obj.z + 0.5f);

        float tMin = (minBounds.x() - rayOrigin.x()) / rayDir.x();
        float tMax = (maxBounds.x() - rayOrigin.x()) / rayDir.x();

        if (tMin > tMax) std::swap(tMin, tMax);

        float tYMin = (minBounds.y() - rayOrigin.y()) / rayDir.y();
        float tYMax = (maxBounds.y() - rayOrigin.y()) / rayDir.y();

        if (tYMin > tYMax) std::swap(tYMin, tYMax);

        if ((tMin > tYMax) || (tYMin > tMax)) return false;

        tMin = std::max(tMin, tYMin);
        tMax = std::min(tMax, tYMax);

        float tZMin = (minBounds.z() - rayOrigin.z()) / rayDir.z();
        float tZMax = (maxBounds.z() - rayOrigin.z()) / rayDir.z();

        if (tZMin > tZMax) std::swap(tZMin, tZMax);

        if ((tMin > tZMax) || (tZMin > tMax)) return false;

        tMin = std::max(tMin, tZMin);
        tMax = std::min(tMax, tZMax);

        return tMax > 0;
    }

    if (obj.type == plane) {
        QVector3D planeNormal(0.0f, 1.0f, 0.0f); // Нормаль плоскости
        QVector3D planePoint(obj.x, obj.y, obj.z); // Точка на плоскости

        float denominator = QVector3D::dotProduct(rayDir, planeNormal);

        if (fabs(denominator) > 1e-6) { // Луч не параллелен плоскости
            float t = QVector3D::dotProduct(planePoint - rayOrigin, planeNormal) / denominator;
            return t >= 0;
        }
        return false; // Луч параллелен плоскости
    }
    return false;
}


QVector3D scene_widget::calculateRayDirection(const QPoint &mouse_pos)
{
    float viewportWidth = this->width();
    float viewportHeight = this->height();

    // Нормализованные координаты устройства (NDC)
    float x = (2.0f * mouse_pos.x()) / viewportWidth - 1.0f;
    float y = 1.0f - (2.0f * mouse_pos.y()) / viewportHeight;
    float z = 1.0f; // Устанавливаем Z = 1 (направление вперёд)

    // Преобразуем NDC в пространство камеры
    QVector4D rayClip = QVector4D(x, y, -1.0f, 1.0f); // -1.0 для обратного направления

    // Преобразуем в пространство вида
    QMatrix4x4 inverseProjection = projectionMatrix.inverted();
    QVector4D rayEye = inverseProjection * rayClip;
    rayEye.setZ(-1.0f); // Устанавливаем Z в -1 (векторное направление)
    rayEye.setW(0.0f);  // Устанавливаем W = 0 для вектора

    // Преобразуем в мировое пространство
    QMatrix4x4 inverseView = viewMatrix.inverted();
    QVector4D rayWorld = inverseView * rayEye;

    // Нормализуем вектор
    QVector3D rayDir = QVector3D(rayWorld.x(), rayWorld.y(), rayWorld.z()).normalized();

    return rayDir;
}