#pragma once

#include <string>
#include <memory>

class BinaryFile
{
public:
    BinaryFile(const std::string &path);
    ~BinaryFile();

    BinaryFile(const BinaryFile &) = delete;
    BinaryFile &operator=(const BinaryFile &) = delete;

    std::unique_ptr<uint8_t[]> dump();

private:
    FILE *m_file;
    size_t m_size;
};
