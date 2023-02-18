#include <Logger/Logger.hpp>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#ifdef __linux__

std::string DOWN_ARROW      =           "\u25BC";
std::string RIGHT_ARROW_WS  =           "    \u25BA ";

#else

std::string DOWN_ARROW      =           "";
std::string RIGHT_ARROW_WS  =           "";

#endif

bool Logger::Init() {
    try {
        std::vector<spdlog::sink_ptr> sinks;
        sinks.push_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_mt>("server.log", 1024 * 1024 * 5, 16));

        auto logger{ std::make_shared<spdlog::logger>("server", sinks.begin(), sinks.end()) };
        logger->set_pattern("[%^%l%$] %v");
        logger->set_level(spdlog::level::debug);
        logger->flush_on(spdlog::level::debug);

        spdlog::register_logger(logger);
        spdlog::set_default_logger(logger);
    }
    catch (const spdlog::spdlog_ex& exception) { 
        return false; 
    }
    return true;
}