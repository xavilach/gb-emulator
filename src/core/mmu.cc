#include "core/mmu.hh"

#define RAM_OFFSET ((uint16_t)0x8000)
#define RAM_SIZE (0x8000)

//TODO Clean up

Mmu::Mmu(Cartridge &cartridge)
    : m_cartridge(cartridge), m_ram(nullptr)
{
    m_ram = std::make_unique<uint8_t[]>(RAM_SIZE);

    if (!m_ram)
    {
        throw std::runtime_error("Allocation failed.");
    }
}

Mmu::~Mmu()
{
}

uint8_t Mmu::readByte(uint16_t address)
{
    if (address < 0x8000) //ROM
    {
        return m_cartridge.read(address);
    }
    else if (address < 0xA000) // VRAM
    {
        uint16_t addr = address - RAM_OFFSET;
        return m_ram[addr];
    }
    else if (address < 0xC000) // External VRAM
    {
        return m_cartridge.read(address);
    }
    else if (address < 0xE000) // RAM
    {
        uint16_t addr = address - RAM_OFFSET;
        return m_ram[addr];
    }
    else if (address < 0xFE00) // Echo RAM
    {
        uint16_t addr = (address - 0x2000) - RAM_OFFSET;
        return m_ram[addr];
    }
    else if (address < 0xFEA0) // OAM RAM
    {
        uint16_t addr = address - RAM_OFFSET;
        return m_ram[addr];
    }
    else if (address < 0xFF00) // Unused
    {
        return 0xFF;
    }
    else if (address < 0xFF80) // IO
    {
        uint16_t addr = address - RAM_OFFSET;
        return m_ram[addr];
    }
    else // HRAM
    {
        uint16_t addr = address - RAM_OFFSET;
        return m_ram[addr];
    }
}

uint16_t Mmu::readWord(uint16_t address)
{
    uint16_t lsb = readByte(address);
    uint16_t msb = readByte(address + 1);

    return (msb << 8) | lsb;
}

void Mmu::writeByte(uint16_t address, uint8_t byte)
{
    if (address < 0x8000) //ROM
    {
        m_cartridge.write(address, byte);
    }
    else if (address < 0xA000) // VRAM
    {
        uint16_t addr = address - RAM_OFFSET;
        m_ram[addr] = byte;
    }
    else if (address < 0xC000) // External VRAM
    {
        m_cartridge.write(address, byte);
    }
    else if (address < 0xE000) // RAM
    {
        uint16_t addr = address - RAM_OFFSET;
        m_ram[addr] = byte;
    }
    else if (address < 0xFE00) // Echo RAM
    {
        uint16_t addr = (address - 0x2000) - RAM_OFFSET;
        m_ram[addr] = byte;
    }
    else if (address < 0xFEA0) // OAM RAM
    {
        uint16_t addr = address - RAM_OFFSET;
        m_ram[addr] = byte;
    }
    else if (address < 0xFF00) // Unused
    {
    }
    else if (address < 0xFF80) // IO
    {
        //TODO
        uint16_t addr = address - RAM_OFFSET;
        m_ram[addr] = byte;
    }
    else // HRAM
    {
        uint16_t addr = address - RAM_OFFSET;
        m_ram[addr] = byte;
    }
}

void Mmu::writeWord(uint16_t address, uint16_t word)
{
    writeByte(address, (uint8_t)word);
    writeByte(address + 1, (uint8_t)(word >> 8));
}
