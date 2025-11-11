#pragma once

#include "stslog/sinks/Sink.hpp"
#include <iostream>

namespace stslog::Sinks
{
    class StdoutSink : public Sink
    {
    public:
        void write(LogLevel lvl, std::string msg) override
        {
            std::cout << this->formatter.content(lvl, std::move(msg)) << std::endl;
        }
    };
}
