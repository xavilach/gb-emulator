#include "core/cpu.hh"

#include "core/mmu.hh"

Cpu::Cpu(Mmu &mmu)
    : m_reg(), m_flags(), m_halted(false), m_mmu(mmu)
{
    m_flags.zero = true;
    m_flags.sub = false;
    m_flags.halfCarry = true;
    m_flags.carry = true;
    m_flags.ime = false;

    m_reg.a = 0x01;
    m_reg.b = 0x00;
    m_reg.c = 0x13;
    m_reg.d = 0x00;
    m_reg.e = 0xD8;
    m_reg.f = 0xB0;
    m_reg.hl = 0x014D;
    m_reg.pc = 0x0100;
    m_reg.sp = 0xFFFE;
}

int Cpu::run()
{
    return 0;
}