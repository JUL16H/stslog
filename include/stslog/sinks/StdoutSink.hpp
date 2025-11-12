#pragma once

#include "stslog/Sink.hpp"
#include <iostream>

namespace stslog::Sinks
{
    class StdoutSink : public Sink
    {
    public:
        void write(std::shared_ptr<LogEvent> pevent) override
        {
            std::cout << pevent->content << '\n';
        }
    };
}
