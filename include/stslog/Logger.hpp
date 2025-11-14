#pragma once
#include <string>
#include <memory>
#include <chrono>
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

        LogEvent generate_event(LogLevel lvl, std::string msg, std::string file, std::string func, int line)
        {
            using namespace std::chrono;
            auto now = floor<microseconds>(system_clock::now());
            auto dp = floor<days>(now);

            year_month_day ymd(dp);
            hh_mm_ss hms(now - dp);

            LogEvent event{
                .lvl = lvl,
                .msg = msg,
                .time = {
                    .year = static_cast<int>(ymd.year()),
                    .month = static_cast<unsigned>(ymd.month()),
                    .day = static_cast<unsigned>(ymd.day()),
                    .hour = static_cast<unsigned>(hms.hours().count()),
                    .minute = static_cast<unsigned>(hms.minutes().count()),
                    .sec = static_cast<unsigned>(hms.seconds().count()),
                    .ms = static_cast<unsigned>(hms.subseconds().count())
                },
                .pos = {
                    .file = std::move(file),
                    .func = std::move(func),
                    .line = line
                }
            };

            return event;
        }

        void log(LogLevel _lvl, std::string msg, std::string file = "?", std::string func = "?", int line = -1)
        {
            if (!shouldLog(_lvl))
                return;

            auto event = generate_event(_lvl, std::move(msg), std::move(file), std::move(func), line);

            for (const auto& [name, p]: pipelines)
                p->log(event);
        }

    private:
        std::string name;
        LogLevel lvl = LogLevel::INFO;
        std::unordered_map<std::string, std::shared_ptr<stslog::LogPipeLine>> pipelines;
    };
}
