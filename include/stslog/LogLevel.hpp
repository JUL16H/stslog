#pragma once
#include <cstdint>
#include <string>

namespace stslog
{
    enum class LogLevel : std::uint8_t
    {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        CRITICAL,
        OFF
    };

    inline std::string lvl2str(LogLevel lvl)
    {
        switch (lvl)
        {
        case LogLevel::TRACE:
            return "TRACE";
        case LogLevel::DEBUG:
            return "DEBUG";
        case LogLevel::INFO:
            return "INFO";
        case LogLevel::WARN:
            return "WARN";
        case LogLevel::ERROR:
            return "ERROR";
        case LogLevel::CRITICAL:
            return "CRITICAL";
        case LogLevel::OFF:
            return "OFF";
        }
        return "UNKNOWN";
    }
}
