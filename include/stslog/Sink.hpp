#pragma once
#include <string>

namespace stslog
{
    class Sink
    {
    public:
        virtual void write(std::string text) = 0;
    };
}
