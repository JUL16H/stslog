#pragma once

#include <string>
#include <memory>

namespace stslog::Sinks
{
    class Sink
    {
    public:
        virtual void write(std::string text) = 0;
    };
}
