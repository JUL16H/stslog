#include "Logger.hpp"
#include <iostream>

namespace stslog
{
    class ConsoleSink : public Sink
    {
    public:
        void write(std::string text) override
        {
            std::cout << text << std::endl;
        }
    };
}
