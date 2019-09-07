#include "core/cartridge.hh"

#include "core/binaryfile.hh"

#include <stdexcept>

//TODO Clean up

Cartridge::Cartridge(const std::string &path)
    : m_rom(nullptr), m_ram(nullptr), m_romBank(1), m_ramBank(0), m_ramBankingMode(false), m_ramEnabled(false)
{
    BinaryFile file(path);

    m_rom = file.dump();
    m_ram = std::make_unique<uint8_t[]>(0x2000);

    switch (type())
    {
    case Type::ROM:
    case Type::MBC1:
    case Type::MBC1_RAM:
    case Type::MBC1_RAM_BATTERY:
        break;

    default:
        throw std::runtime_error("Unsupported cartridge type.");
    }
}

Cartridge::~Cartridge()
{
}

Cartridge::Type Cartridge::type()
{
    return Type(m_rom[0x147]);
}

uint8_t Cartridge::read(uint16_t address)
{
    switch (type())
    {
    case Type::ROM:
        if (address >= 0xA000)
        {
            uint16_t addr = address - (uint16_t)0xA000;
            return m_ram[addr];
        }
        else
        {
            return m_rom[address];
        }
        break;

    case Type::MBC1:
    case Type::MBC1_RAM:
    case Type::MBC1_RAM_BATTERY:
        if (address >= 0xA000)
        {
            if (m_ramEnabled)
            {
                uint16_t addr = address - 0xA000;
                addr += (uint16_t)m_ramBank * (uint16_t)0x2000;

                return m_ram[addr];
            }
            else
            {
                return 0xFF;
            }
        }
        else
        {
            if (address < 0x4000)
            {
                /* Bank 0. */
                return m_rom[address];
            }
            else
            {
                uint32_t addr = (uint32_t)(address - (uint16_t)0x4000);
                addr += (uint32_t)m_romBank * (uint32_t)0x4000;

                /* Bank n. */
                return m_rom[addr];
            }
        }
        break;

    default:
        return 0xFF;
    }
}

void Cartridge::write(uint16_t address, uint8_t data)
{
    switch (type())
    {
    case Type::ROM:
        if (address >= 0xA000)
        {
            uint16_t addr = address - (uint16_t)0xA000;
            m_ram[addr] = data;
        }
        break;

    case Type::MBC1:
    case Type::MBC1_RAM:
    case Type::MBC1_RAM_BATTERY:
        if (address >= 0xA000)
        {
            if (m_ramEnabled)
            {
                uint16_t addr = address - 0xA000;
                addr += (uint16_t)m_ramBank * (uint16_t)0x2000;

                m_ram[addr] = data;
            }
        }
        else
        {
            if (address < 0x2000)
            {
                // ram enable
                data &= 0x0F;

                m_ramEnabled = (0x0A == data);
            }
            else if (address < 0x4000)
            {
                // ROM bank number
                data &= 0x1F;
                if (0 == data)
                {
                    data = 0x01;
                }
                m_romBank &= 0xE0;
                m_romBank |= data;
            }
            else if (address < 0x6000)
            {
                //RAM bank number or ROM bank number
                data &= 0x03;
                if (m_ramBankingMode)
                {
                    m_ramBank = data;
                }
                else
                {
                    m_romBank &= 0x1F;
                    m_romBank |= (data << 5);
                }
            }
            else
            {
                //ROM/RAM mode select
                m_ramBankingMode = (0 != (data & 0x01));
            }
        }

        break;

    default:
        break;
    }
}
