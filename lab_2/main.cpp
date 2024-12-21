//Compile arguments g++ main.cpp -o glew_test -lGLEW -lGL -lGLU -lglut
#include <GL/glew.h>
#include <GL/glut.h>
#include <cmath>

// Угол вращения
float angle = 0.0f;

// Позиции источников света
float light1X = 2.0f, light1Y = 2.0f, light1Z = 0.0f;
float light2X = -2.0f, light2Y = 2.0f, light2Z = 0.0f;

void drawCube() {
    glutSolidCube(1.0); // Рисуем куб
}

void drawPyramid() {
    glBegin(GL_TRIANGLES);

    // Передняя грань
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Правая грань
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);

    // Задняя грань
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);

    // Левая грань
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    glEnd();

    // Основание пирамиды
    glBegin(GL_QUADS);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glEnd();
}

void drawCylinder(float radius, float height, int slices) {
    glBegin(GL_QUAD_STRIP);

    for (int i = 0; i <= slices; ++i) {
        float angle = 2.0f * M_PI * i / slices;
        float x = radius * cos(angle);
        float z = radius * sin(angle);

        glVertex3f(x, 0.0f, z);           // Нижнее основание
        glVertex3f(x, height, z);        // Верхнее основание
    }

    glEnd();

    // Рисуем верхний и нижний круги
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, 0.0f, 0.0f);      // Центр нижнего основания
    for (int i = 0; i <= slices; ++i) {
        float angle = 2.0f * M_PI * i / slices;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        glVertex3f(x, 0.0f, z);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0.0f, height, 0.0f);    // Центр верхнего основания
    for (int i = 0; i <= slices; ++i) {
        float angle = 2.0f * M_PI * i / slices;
        float x = radius * cos(angle);
        float z = radius * sin(angle);
        glVertex3f(x, height, z);
    }
    glEnd();
}

void drawLightSource(float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z); // Перемещаем сферу в нужное положение
    glutSolidSphere(0.2, 16, 16);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(0.0f, 5.0f, 10.0f,   // Позиция камеры
              0.0f, 0.0f, 0.0f,    // Точка, на которую смотрит камера
              0.0f, 1.0f, 0.0f);   // Вверх по оси Y

    // Рисуем куб
    glPushMatrix();
    glTranslatef(-2.0f, 0.0f, 0.0f);
    drawCube();
    glPopMatrix();

    // Рисуем пирамиду
    glPushMatrix();
    glTranslatef(2.0f, 0.0f, 0.0f);
    drawPyramid();
    glPopMatrix();

    // Рисуем цилиндр
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -3.0f);
    drawCylinder(0.5f, 2.0f, 32);
    glPopMatrix();

    // Рисуем источники света
    glColor3f(1.0f, 1.0f, 0.0f);
    drawLightSource(light1X, light1Y, light1Z);
    drawLightSource(light2X, light2Y, light2Z);

    glutSwapBuffers();
}

void update() {
    // Обновляем угол вращения для анимации (опционально)
    angle += 0.1f;
    if (angle > 360.0f) angle -= 360.0f;

    glutPostRedisplay();
}

void keys(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': light1Y += 0.1f; break; // Двигаем первый источник света вверх
        case 's': light1Y -= 0.1f; break; // Двигаем первый источник света вниз
        case 'a': light1X -= 0.1f; break; // Двигаем первый источник света влево
        case 'd': light1X += 0.1f; break; // Двигаем первый источник света вправо

        case 'i': light2Y += 0.1f; break; // Двигаем второй источник света вверх
        case 'k': light2Y -= 0.1f; break; // Двигаем второй источник света вниз
        case 'j': light2X -= 0.1f; break; // Двигаем второй источник света влево
        case 'l': light2X += 0.1f; break; // Двигаем второй источник света вправо

        case 27: exit(0); // Завершаем программу по нажатию Esc
    }
    glutPostRedisplay();
}

void init() {
    glEnable(GL_DEPTH_TEST); // Включаем тест глубины

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f); // Устанавливаем перспективную проекцию

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("3D Scene with Lights");

    glewInit();
    init();

    glutDisplayFunc(display);
    glutIdleFunc(update);
    glutKeyboardFunc(keys);

    glutMainLoop();
    return 0;
}