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

        bool add_sink(std::string name, std::shared_ptr<Sinks::Sink> sink)
        {
            if (this->pipelines.count(name)) return false;
            pipelines[name] = std::make_shared<LogPipeLine>(sink);
            return true;
        }
        void erase_sink(std::string name) { pipelines.erase(name); }
        void set_level(LogLevel _lvl) { this->lvl = _lvl; }

        void set_format(std::string format)
        {
            for (auto it: pipelines)
                it.second->set_format(format);
        }

        void set_format(std::string name, std::string format)
        {
            if (!pipelines.count(name))
                return;
            pipelines[name]->set_format(std::move(format));
        }

        void trace(std::string msg) { log(LogLevel::TRACE, msg); }
        void debug(std::string msg) { log(LogLevel::DEBUG, msg); }
        void info(std::string msg) { log(LogLevel::INFO, msg); }
        void warn(std::string msg) { log(LogLevel::WARN, msg); }
        void error(std::string msg) { log(LogLevel::ERROR, msg); }
        void critical(std::string msg) { log(LogLevel::CRITICAL, msg); }

    private:
        bool shouldLog(LogLevel _lvl)
        {
            return this->lvl <= _lvl && !this->pipelines.empty();
        }

        void log(LogLevel _lvl, std::string msg, std::string file = "", std::string func = "", unsigned line = 0)
        {
            if (!shouldLog(_lvl))
                return;
            auto event = LogEvent(_lvl, std::move(msg));
            event.fillInfo();
            if (!file.empty())
                event.pos = {
                    .file = std::move(file),
                    .func = std::move(func),
                    .line = line
                };
            for (const auto& [name, p]: pipelines)
                p->log(event);
        }

    private:
        std::string name;
        LogLevel lvl = LogLevel::INFO;
        std::unordered_map<std::string, std::shared_ptr<stslog::LogPipeLine>> pipelines;
    };
}
