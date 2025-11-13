#pragma once
#include <string>
#include <memory>
#include <unordered_map>
#include "stslog/LogLevel.hpp"
#include "stslog/LogPipeLine.hpp"

namespace stslog
{
    class Logger

    {
    public:
        Logger(std::string _name) : name(std::move(_name)) {}

        void add_sink(std::string name, std::shared_ptr<Sinks::Sink> sink)
        {
            pipelines[name] = std::make_shared<LogPipeLine>(sink);
        }

        // void add_sink(std::vector<>)

        void erase_sink(std::string name) { pipelines.erase(name); }

        void set_level(LogLevel _lvl) { this->lvl = _lvl; }

        void trace(std::string msg) { log(LogLevel::TRACE, msg); }
        void debug(std::string msg) { log(LogLevel::DEBUG, msg); }
        void info(std::string msg) { log(LogLevel::INFO, msg); }
        void warn(std::string msg) { log(LogLevel::WARN, msg); }
        void error(std::string msg) { log(LogLevel::ERROR, msg); }
        void critical(std::string msg) { log(LogLevel::CRITICAL, msg); }

    private:
        bool shouldLog(LogLevel _lvl)
        {
            return this->lvl <= _lvl;
        }

        void log(LogLevel _lvl, std::string msg)
        {
            if (!shouldLog(_lvl))
                return;
            auto pevent = std::make_shared<LogEvent>(_lvl, std::move(msg));
            for (const auto it: pipelines)
                it.second->log(pevent);
        }

    private:
        std::string name;
        LogLevel lvl = LogLevel::INFO;
        std::unordered_map<std::string, std::shared_ptr<stslog::LogPipeLine>> pipelines;
    };
}
