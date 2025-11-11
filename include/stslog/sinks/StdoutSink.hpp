#pragma once

#include "stslog/sinks/Sink.hpp"
#include <iostream>

namespace stslog::Sinks
{
    class StdoutSink : public Sink
    {
    public:
        void write(std::string msg) override
        {
            std::cout << this->formatter.content() << std::endl;
        }
    };
}
