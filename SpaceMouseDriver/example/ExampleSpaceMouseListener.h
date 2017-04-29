#pragma once
#include "../driver/SpaceMouseListener.h"
#include <iostream>

class ExampleSpaceMouseListener : public SpaceMouseListener
{
public:
    ExampleSpaceMouseListener();

    bool isSpaceMouseActive() override;
    void setSpaceMouseActive(bool value) override;
    void spaceMouseMovement(const int &TX, const int &TY, const int &TZ, const int &RX, const int &RY, const int &RZ) override;
    void spaceMouseButton(const int &id) override;
private:
    bool space_mouse_active = false;
};

