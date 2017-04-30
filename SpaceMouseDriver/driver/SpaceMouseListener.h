#pragma once


class SpaceMouseListener
{
public:
    virtual bool isSpaceMouseActive() = 0;
    virtual void setSpaceMouseActive(bool value) = 0;
    virtual void spaceMouseMovement(const int &TX, const int &TY, const int &TZ, const int &RX, const int &RY, const int &RZ) = 0;
    virtual void spaceMouseButton(const int &id) = 0;
};

