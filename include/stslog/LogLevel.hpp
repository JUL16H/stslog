#pragma once

#include <cstdint>

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
}
