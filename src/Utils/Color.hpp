#pragma once
#include <string>

class Color {
public:
    Color(const uint8_t& r, const uint8_t& g, const uint8_t& b, const uint8_t& a = 255) {
        m_color[0] = b;
        m_color[1] = g;
        m_color[2] = r;
        m_color[3] = a;
    }
    Color(const uint32_t& col) {
        m_color[0] = (col >> 24) & 0xFF;
        m_color[1] = (col >> 16) & 0xFF;
        m_color[2] = (col >> 8) & 0xFF;
        m_color[3] = (col) & 0xFF;
    }
    Color() {
        for (auto index = 0; index < sizeof(uint32_t); index++)
            m_color[index] = 0xFF;
    }
    ~Color() = default;

    uint32_t GetInt() const {
        uint32_t result = 0;
        for (auto index = 0; index < sizeof(uint32_t); index++)
            result = (result << 8) + m_color[index];
        return result;
    }

    void SetRed(const uint8_t& col) { m_color[2] = col; }
    [[nodiscard]] uint8_t GetRed() const { return m_color[2]; }
    void SetGreen(const uint8_t& col) { m_color[1] = col; }
    [[nodiscard]] uint8_t GetGreen() const { return m_color[1]; }
    void SetBlue(const uint8_t& col) { m_color[0] = col; }
    [[nodiscard]] uint8_t GetBlue() const { return m_color[0]; }
    void SetAlpha(const uint8_t& col) { m_color[3] = col; }
    [[nodiscard]] uint8_t GetAlpha() const { return m_color[3]; }
    
private:
    uint8_t m_color[4];
};