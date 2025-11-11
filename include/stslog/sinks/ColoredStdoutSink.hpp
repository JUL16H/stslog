#pragma once

#include "stslog/sinks/Sink.hpp"
#include <iostream>

namespace stslog::Sinks
{
    class ColoredStdoutSink : public Sink
    {
    public:
        void write(LogLevel lvl, std::string msg) override
        {
            std::string color;
            switch (lvl)
            {
            case LogLevel::TRACE:
                color = "\033[37m"; break;
            case LogLevel::DEBUG:
                color = "\033[36m"; break;
            case LogLevel::INFO:
                color = "\033[32m"; break;
            case LogLevel::WARN:
                color = "\033[33m"; break;
            case LogLevel::ERROR:
                color = "\033[31m"; break;
            case LogLevel::CRITICAL:
                color = "\033[1;41m"; break;
            default:
                color = "";
            }
            std::cout << color << this->formatter.content(lvl, std::move(msg)) << "\033[0m" << '\n';
        }
    };
}
