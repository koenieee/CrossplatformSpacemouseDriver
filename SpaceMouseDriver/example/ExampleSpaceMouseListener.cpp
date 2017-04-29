#include "ExampleSpaceMouseListener.h"

ExampleSpaceMouseListener::ExampleSpaceMouseListener()
{

}

bool ExampleSpaceMouseListener::isSpaceMouseActive()
{
    std::cout << "ExampleSpaceMouseListener::isSpaceMouseActive? " << space_mouse_active << "\n";
    return space_mouse_active;
}

void ExampleSpaceMouseListener::setSpaceMouseActive(bool value)
{
    std::cout << "ExampleSpaceMouseListener::setSpaceMouseActive: " << value<< "\n";
    space_mouse_active = value;
}

void ExampleSpaceMouseListener::spaceMouseMovement(const int &TX, const int &TY, const int &TZ, const int &RX, const int &RY, const int &RZ)
{
    std::cout << "ExampleSpaceMouseListener::spaceMouseMovement: ";
    std::cout << " tx: " << TX <<
                 " ty: " << TY <<
                 " tz: " << TZ <<
                 " rx: " << RX <<
                 " ry: " << RY <<
                 " rz: " << RZ<< "\n";
}

void ExampleSpaceMouseListener::spaceMouseButton(const int &id)
{
    std::cout << "ExampleSpaceMouseListener::spaceMouseButton: " << id<< "\n";
}
