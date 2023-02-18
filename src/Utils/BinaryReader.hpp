#pragma once
#include <vector>
#include <cstdint>
#include <memory>
#include <string>

class BinaryReader {
public:
    template <typename T>
    T Read() {
        T val;
        std::memcpy(&val, m_pData + m_position, sizeof(T));
        m_position += sizeof(T);
        return val;
    }
    std::string ReadStringU16() {
        uint16_t valLength{ this->Read<uint16_t>() };
        std::string val{ reinterpret_cast<char*>(m_pData + m_position), valLength };
        m_position += valLength;
        return val;
    }
    std::string ReadStringU32() {
        uint32_t valLength{ this->Read<uint32_t>() };
        std::string val{ reinterpret_cast<char*>(m_pData + m_position), valLength };
        m_position += valLength;
        return val;
    }

    void Skip(std::size_t length) { m_position += length; }
    std::size_t GetPosition() const { return m_position; }

public:
    BinaryReader(void* pData) : m_pData(static_cast<uint8_t*>(pData)), m_position(0) {}
    ~BinaryReader() = default;

private:
    uint8_t* m_pData;
    std::size_t m_position;
};
