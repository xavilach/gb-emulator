#include "core/timer.hh"

#define TIMER_REG_DIV (0xFF04)
#define TIMER_REG_TIMA (0xFF05)
#define TIMER_REG_TMA (0xFF06)
#define TIMER_REG_TAC (0xFF07)

Timer::Timer(Mmu &mmu)
    : m_divCounter(0), m_timCounter(0), m_timClock(0), m_mmu(mmu)
{
}

void Timer::run()
{
    m_divCounter += 1;

    if (m_divCounter >= 256)
    {
        m_divCounter = 0;

        uint8_t div = m_mmu.readByte(TIMER_REG_DIV) + 1;

        m_mmu.writeByte(TIMER_REG_DIV, div);
    }

    uint8_t tac = m_mmu.readByte(TIMER_REG_TAC);

    if ((tac >> 2) & 0x01)
    {
        //timer enabled.
        switch (tac & 0x03)
        {
        case 0:
            m_timClock = 1024;
            break;
        case 1:
            m_timClock = 16;
            break;
        case 2:
            m_timClock = 64;
            break;
        case 3:
            m_timClock = 256;
            break;
        }

        m_timCounter += 1;

        if (m_timCounter >= m_timClock)
        {
            m_timCounter = 0;

            uint8_t tima = m_mmu.readByte(TIMER_REG_TIMA);

            if (0xFF == tima)
            {
                uint8_t tma = m_mmu.readByte(TIMER_REG_TMA);

                tima = tma;

                m_mmu.writeByte(TIMER_REG_TIMA, tima);

                uint8_t irq_flags = m_mmu.readByte(0xFF0F);

                irq_flags |= (1 << 2);

                m_mmu.writeByte(0xFF0F, irq_flags);
            }
            else
            {
                tima += 1;

                m_mmu.writeByte(TIMER_REG_TIMA, tima);
            }
        }
    }
}
