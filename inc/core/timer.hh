#pragma once

#include "core/mmu.hh"

#include <cstdint>

class Timer
{
public:
    Timer(Mmu &mmu);

    void run();

private:
    uint16_t m_divCounter;
    uint16_t m_timCounter;
    uint16_t m_timClock;

    Mmu &m_mmu;
};
