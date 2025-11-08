#pragma once

#include <string>

namespace stslog::Sinks
{
    class Sink
    {
    public:
        virtual void write(std::string text) = 0;
        virtual ~Sink() {}
    };
}
