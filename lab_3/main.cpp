#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

// Данные для камеры
float cameraDistance = 5.0f;  // Расстояние камеры от сферы
float pitch = 0.0f;           // Угол наклона камеры
float yaw = -90.0f;           // Угол поворота камеры (начинаем с "-90" для корректной ориентации)
const float PITCH_LIMIT = 89.0f; // Ограничение наклона камеры

float lastX = 400, lastY = 300; // Координаты мыши
bool firstMouse = true;

// Обработка изменения размера окна
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Обработка скроллинга - изменение расстояния до камеры
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    cameraDistance -= yoffset * 0.5f;
    if (cameraDistance < 1.0f)
        cameraDistance = 1.0f;
    if (cameraDistance > 20.0f)
        cameraDistance = 20.0f;
}

// Обработка мыши - вращение камеры
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // Ограничение наклона камеры
    if (pitch > PITCH_LIMIT)
        pitch = PITCH_LIMIT;
    if (pitch < -PITCH_LIMIT)
        pitch = -PITCH_LIMIT;
}

// Обработка клавиш для закрытия окна
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// Рисование сферы с использованием линий
void drawSphere(float radius, int sectors, int stacks) {
    for (int i = 0; i <= stacks; ++i) {
        float stackAngle = M_PI / 2 - i * M_PI / stacks; // от pi/2 до -pi/2
        float xy = radius * cos(stackAngle);            // Радиус горизонтального круга
        float z = radius * sin(stackAngle);             // Высота

        glBegin(GL_LINE_LOOP);
        for (int j = 0; j <= sectors; ++j) {
            float sectorAngle = j * 2 * M_PI / sectors; // от 0 до 2*pi
            float x = xy * cos(sectorAngle);
            float y = xy * sin(sectorAngle);
            glVertex3f(x, y, z);
        }
        glEnd();
    }
}

int main() {
    // Инициализация GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Настройка окна
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); // Совместимость с OpenGL

    GLFWwindow* window = glfwCreateWindow(800, 600, "Modern Sphere Rendering", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Инициализация GLEW
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glEnable(GL_DEPTH_TEST); // Включаем тест глубины

    // Обратные вызовы
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Захват мыши

    // Цикл рендеринга
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // Очистка буферов
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Установка матриц проекции и вида через glm
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        glm::mat4 view = glm::lookAt(
                glm::vec3(cameraDistance * cos(glm::radians(pitch)) * cos(glm::radians(yaw)),
                          cameraDistance * sin(glm::radians(pitch)),
                          cameraDistance * cos(glm::radians(pitch)) * sin(glm::radians(yaw))),
                glm::vec3(0.0f, 0.0f, 0.0f), // Точка, куда смотрит камера
                glm::vec3(0.0f, 1.0f, 0.0f)  // Вектор "вверх"
        );

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glMultMatrixf(&projection[0][0]);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glMultMatrixf(&view[0][0]);

        // Рисование сферы
        drawSphere(1.0f, 36, 18);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}