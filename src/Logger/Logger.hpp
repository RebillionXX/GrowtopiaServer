#pragma once
#include <string>
#include <spdlog/spdlog.h>
#include <spdlog/formatter.h>
#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/chrono.h>

enum eLoggerType{
    INFO,
    WARNING,
    EXCEPTION
};

class Logger {
public:
    static bool Init();

public:
    template <typename... Args>
    static void Print(eLoggerType type, const std::string& format, Args&&... args) {
        switch (type) {
        case eLoggerType::WARNING: {
            spdlog::warn(fmt::vformat(format, fmt::make_format_args(args...)));
        } break;
        case eLoggerType::EXCEPTION: {
            spdlog::error(fmt::vformat(format, fmt::make_format_args(args...)));
        } break;
        default: {
            spdlog::info(fmt::vformat(format, fmt::make_format_args(args...)));
        } break;
        }
    }

    template <typename... Args>
    static void Print(const std::string& format, Args&&... args) {
        fmt::print("{}\n", fmt::vformat(format, fmt::make_format_args(args...)));
    }
};