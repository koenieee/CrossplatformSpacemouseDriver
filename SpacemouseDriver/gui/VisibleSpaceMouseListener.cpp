#include "VisibleSpaceMouseListener.h"

VisibleSpaceMouseListener::VisibleSpaceMouseListener()
{

}

bool VisibleSpaceMouseListener::isSpaceMouseActive()
{
    std::cout << "VisibleSpaceMouseListener::isSpaceMouseActive? " << space_mouse_active;
    return space_mouse_active;
}

void VisibleSpaceMouseListener::setSpaceMouseActive(bool value)
{
    std::cout << "VisibleSpaceMouseListener::setSpaceMouseActive: " << value;
    space_mouse_active = value;
}

void VisibleSpaceMouseListener::spaceMouseMovement(const int &TX, const int &TY, const int &TZ, const int &RX, const int &RY, const int &RZ)
{
    std::cout << "VisibleSpaceMouseListener::spaceMouseMovement: ";
    std::cout << "tx: " << TX <<
                 "ty: " << TY <<
                 "tz: " << TZ <<
                 "rx: " << RX <<
                 "ry: " << RY <<
                 "rz: " << RZ;
}

void VisibleSpaceMouseListener::spaceMouseButton(const int &id)
{
    std::cout << "VisibleSpaceMouseListener::spaceMouseButton: " << id;
}
