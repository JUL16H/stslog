#pragma once
#include "stslog//Sink.hpp"

namespace stslog::Sinks {
    struct TestSink : public Sink {
        void write(const LogEvent &event) override {
            this->event = event;
        }
        LogEvent event;
    };
}
