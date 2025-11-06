#pragma once

#include <string.h>
#include "LogLevel.hpp"
#include "Sink.hpp"

namespace stslog
{
    class Logger
    {
    public:
        void log(LogLevel _lvl, std::string text)
        {
            if (this->lvl >= _lvl)
                sink->write(text);
        }

    private:
        LogLevel lvl = LogLevel::DEBUG;
        Sink *sink;
    };
}
