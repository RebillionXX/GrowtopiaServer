#pragma once
#include <vector>
#include <string>
#include <cstring>
#include <fmt/core.h>

class BinaryWriter {
public:
    template <typename T>
    void Write(T val) {
        std::memcpy(m_pBuffer + m_position, &val, sizeof(T));
        m_position += sizeof(T);
    }
    template <typename T>
    void Write(const T* val, std::size_t dataLength) {
        std::memcpy(m_pBuffer + m_position, val, dataLength);
        m_position += dataLength;
    }
    void Write(std::string val, std::size_t dataSize = sizeof(uint16_t)) {
        std::size_t valLength = val.size();
        std::memcpy(m_pBuffer + m_position, &valLength, dataSize);
        std::memcpy(m_pBuffer + m_position + dataSize, val.c_str(), valLength);
        m_position += valLength + dataSize;
    }

    void Skip(std::size_t length) { m_position += length; }
    uint8_t* Get() { return m_pBuffer; }
    std::size_t GetPosition() const { return m_position; }
    
public:
    BinaryWriter(uint8_t* data, std::size_t pos = 0) : m_pBuffer(data), m_position(pos), m_destructor(false) {}
    BinaryWriter(std::size_t size) : m_position(0), m_destructor(true) {
        m_pBuffer = (uint8_t*)std::malloc(size);
        std::memset(m_pBuffer, 0, size);
    }
    ~BinaryWriter() {
        if (this->m_destructor && m_pBuffer)
            std::free(m_pBuffer);
    }

private:
    uint8_t* m_pBuffer;
    std::size_t m_position;

    bool m_destructor;
};