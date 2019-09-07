#pragma once

#include "core/mmu.hh"

class Joypad
{
public:
    Joypad(Mmu &mmu);

    void setRight(bool pressed);
    void setLeft(bool pressed);
    void setUp(bool pressed);
    void setDown(bool pressed);
    void setA(bool pressed);
    void setB(bool pressed);
    void setStart(bool pressed);
    void setReset(bool pressed);

    void update();

private:
    struct Directions
    {
        bool right;
        bool left;
        bool up;
        bool down;
    } m_directions;

    struct Buttons
    {
        bool a;
        bool b;
        bool start;
        bool reset;
    } m_buttons;

    Mmu &m_mmu;
};
