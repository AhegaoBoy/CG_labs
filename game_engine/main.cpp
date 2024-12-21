#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Установка параметров OpenGL: версия 3.3, профиль совместимости
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setVersion(3, 3); // OpenGL 3.3
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);

    QSurfaceFormat::setDefaultFormat(format);

    MainWindow window;
    window.show(); // Показываем окно

    return app.exec(); // Запускаем главный цикл приложения
}