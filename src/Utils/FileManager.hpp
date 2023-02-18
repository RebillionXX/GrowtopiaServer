#pragma once
#include <string_view>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>

namespace FileManager {
    inline uint8_t* ReadAsBytes(std::string_view path, size_t& fileSize) noexcept {
        std::ifstream file{ path.data(), std::ifstream::in | std::ifstream::binary };
        if (!file.is_open())
            return nullptr;
        fileSize = file.seekg(0, std::ios::end).tellg();
        uint8_t* data = (uint8_t*)std::malloc(fileSize);

        file.seekg(0, std::ios::beg);
        file.read(reinterpret_cast<char*>(data), static_cast<std::streamsize>(fileSize));
        file.close();   

        return data;
    }
    inline std::vector<uint8_t> ReadAsByteArray(std::string_view path) noexcept {
        std::ifstream file{ path.data(), std::ifstream::in | std::ifstream::binary };
        if (!file.is_open())
            return std::vector<uint8_t>{};
        size_t fileSize = file.seekg(0, std::ios::end).tellg();
        std::vector<uint8_t> data{};
        data.resize(fileSize);

        file.seekg(0, std::ios::beg);
        file.read(reinterpret_cast<char*>(data.data()), static_cast<std::streamsize>(fileSize));
        file.close();   

        return data;
    }
    inline bool WriteAsBytes(std::string_view path, char* pData, const size_t& dataLength) noexcept {
        std::ofstream file{ path.data(), std::ios::out | std::ios::binary };
        if (!file.is_open())
            return false;

        file.seekp(0, std::ios::beg);
        file.write(pData, static_cast<std::streamsize>(dataLength));
        file.close();   

        return true;
    }
}