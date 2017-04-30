#include "gui/MainWidget.h"
#include "driver/SpaceMouseController.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget w;

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);
    SpaceMouseController * current_controller = new SpaceMouseController(&w);

    //just using the variable to disable the compiler warning current-controller isn't used.
    (void)current_controller;

    w.show();
    return  a.exec();
}
