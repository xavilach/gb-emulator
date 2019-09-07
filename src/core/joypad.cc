#include "core/Joypad.hh"

Joypad::Joypad(Mmu &mmu)
    : m_directions(), m_buttons(), m_mmu(mmu)
{
}

void Joypad::setRight(bool pressed)
{
    m_directions.right = pressed;
}

void Joypad::setLeft(bool pressed)
{
    m_directions.left = pressed;
}

void Joypad::setUp(bool pressed)
{
    m_directions.up = pressed;
}

void Joypad::setDown(bool pressed)
{
    m_directions.down = pressed;
}

void Joypad::setA(bool pressed)
{
    m_buttons.a = pressed;
}

void Joypad::setB(bool pressed)
{
    m_buttons.b = pressed;
}

void Joypad::setStart(bool pressed)
{
    m_buttons.start = pressed;
}

void Joypad::setReset(bool pressed)
{
    m_buttons.reset = pressed;
}

void Joypad::update()
{
    uint8_t reg = m_mmu.readByte(0xFF00);

    uint8_t type = (reg >> 4) & 0x03;

    switch (type)
    {
    case 1:
        reg &= 0xF0;

        if (m_directions.right)
            reg |= (1 << 0);
        if (m_directions.left)
            reg |= (1 << 1);
        if (m_directions.up)
            reg |= (1 << 2);
        if (m_directions.down)
            reg |= (1 << 3);

        m_mmu.writeByte(0xFF00, reg);
        break;

    case 2:
        reg &= 0xF0;

        if (m_buttons.a)
            reg |= (1 << 0);
        if (m_buttons.b)
            reg |= (1 << 1);
        if (m_buttons.reset)
            reg |= (1 << 2);
        if (m_buttons.start)
            reg |= (1 << 3);

        m_mmu.writeByte(0xFF00, reg);
        break;

    default:
        break;
    }
}
