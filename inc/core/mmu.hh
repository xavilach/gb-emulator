#pragma once

#include "core/cartridge.hh"

#include <memory>

class Mmu
{
public:
    Mmu(Cartridge &cartridge);
    ~Mmu();

    uint8_t readByte(uint16_t address);
    uint16_t readWord(uint16_t address);

    void writeByte(uint16_t address, uint8_t byte);
    void writeWord(uint16_t address, uint16_t word);

private:
    Cartridge &m_cartridge;
    std::unique_ptr<uint8_t[]> m_ram;
};
