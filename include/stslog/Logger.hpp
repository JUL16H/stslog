#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <memory>
#include "Sink.hpp"
#include "stslog/LogLevel.hpp"
#include "stslog/Sink.hpp"

namespace stslog
{
    class Logger
    {
    public:
        Logger(std::string _name) : name(std::move(_name)) {}
        Logger(std::string _name, std::shared_ptr<Sinks::Sink> sink) : name(_name)
         { this->sinks.push_back(sink); }
        Logger(std::string _name, std::vector<std::shared_ptr<Sinks::Sink>> _sinks)
         : name(std::move(_name)), sinks(std::move(_sinks)) {}

        void trace(std::string text) { log(LogLevel::TRACE, text); }
        void debug(std::string text) { log(LogLevel::DEBUG, text); }
        void info(std::string text) { log(LogLevel::INFO, text); }
        void warn(std::string text) { log(LogLevel::WARN, text); }
        void error(std::string text) { log(LogLevel::ERROR, text); }
        void critical(std::string text) { log(LogLevel::CRITICAL, text); }

        void changeSink(std::shared_ptr<Sinks::Sink> _sink) noexcept
        {
            this->sinks.clear();
            this->sinks.emplace_back(_sink);
        }
        void changeSink(std::vector<std::shared_ptr<Sinks::Sink>> _sinks) noexcept
         { this->sinks = std::move(_sinks); }

    private:
        void log(LogLevel _lvl, std::string text)
        {
            if (this->lvl >= _lvl)
                for (auto s: this->sinks)
                    s->write(text);
        }

        std::string name;
        LogLevel lvl = LogLevel::INFO;
        std::vector<std::shared_ptr<Sinks::Sink>> sinks;
    };
}
