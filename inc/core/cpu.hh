#pragma once

#include "core/mmu.hh"

#include <cstdint>

class Cpu
{
public:
    Cpu(Mmu &mmu);

    int run();

private:
    struct Registers
    {
        uint8_t a;
        uint8_t b;
        uint8_t c;
        uint8_t d;
        uint8_t e;
        uint8_t f;
        uint16_t hl;
        uint16_t pc;
        uint16_t sp;
    } m_reg;

    struct Flags
    {
        bool zero;
        bool sub;
        bool halfCarry;
        bool carry;
        bool ime;
    } m_flags;

    bool m_halted;

    Mmu &m_mmu;
};
