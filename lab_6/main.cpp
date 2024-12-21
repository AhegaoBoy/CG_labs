#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    main_window window(nullptr);
    window.show();

    return app.exec();
}
