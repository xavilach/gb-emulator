#include "core/binaryfile.hh"

BinaryFile::BinaryFile(const std::string &path)
    : m_file(nullptr), m_size(0)
{
    m_file = fopen(path.c_str(), "rb");

    if (!m_file)
    {
        throw std::runtime_error("fopen failed.");
    }

    fseek(m_file, 0, SEEK_END);
    m_size = (size_t)ftell(m_file);
    fseek(m_file, 0, SEEK_SET);

    if ((m_size < 0x150) || (m_size > 0x800000))
    {
        throw std::runtime_error("Invalid file size.");
    }
}

BinaryFile::~BinaryFile()
{
    if (m_file)
    {
        fclose(m_file);
    }
}

std::unique_ptr<uint8_t[]> BinaryFile::dump()
{
    std::unique_ptr<uint8_t[]> buffer = std::make_unique<uint8_t[]>(m_size);

    if (!buffer)
    {
        throw std::runtime_error("Failed to allocate.");
    }

    (void)fread(buffer.get(), m_size, 1, m_file);

    return buffer;
}
