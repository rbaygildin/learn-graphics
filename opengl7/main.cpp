
#include <QApplication>
#include <QGLFormat>
#include "MainWindow.h"

/**
 * Entry point
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
    QApplication app(argc, argv);
//    QSurfaceFormat glFormat;
//    glFormat.setVersion(3, 3);
//    glFormat.setProfile(QSurfaceFormat::CoreProfile);
//    QSurfaceFormat::setDefaultFormat(glFormat);
    MainWindow wnd;
    wnd.show();
    return app.exec();
}