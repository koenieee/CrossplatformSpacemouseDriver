#include "gui/visible3dobject.h"
#include "gui/VisibleSpaceMouseListener.h"
#include "driver/SpaceMouseController.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Visible3DObject w;


    SpaceMouseListener * the_listener = new VisibleSpaceMouseListener();
    SpaceMouseController * current_controller = new SpaceMouseController(the_listener);

    w.show();
    return a.exec();
}
