#pragma once
#include "stslog/Sink.hpp"
#include <iostream>

namespace stslog::Sinks {

    class StdoutSink : public Sink {
    public:
        void write(const LogEvent &event) override {
            std::cout << event.content << '\n';
        }
    };

}
