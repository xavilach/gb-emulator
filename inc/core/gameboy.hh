#pragma once

#include "core/mmu.hh"
#include "core/cartridge.hh"

class Gameboy
{
public:
    Gameboy(const std::string &path);
    ~Gameboy();

private:
    Cartridge m_cartridge;
    Mmu m_mmu;
};
