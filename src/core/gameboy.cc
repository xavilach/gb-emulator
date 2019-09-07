#include "core/gameboy.hh"

Gameboy::Gameboy(const std::string &path)
    : m_cartridge(path), m_mmu(m_cartridge)
{
}

Gameboy::~Gameboy()
{
}
