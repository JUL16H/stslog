#pragma once
#include <memory>
#include <chrono>
#include <unordered_map>
#include <format>
#include <vector>
#include <utility>
#include "stslog/LogLevel.hpp"
#include "stslog/LogPipeLine.hpp"

namespace stslog {

    class Logger {
        friend class LogRegistry;
    public:
        Logger(std::string loggerName, std::string sinkName, std::shared_ptr<Sinks::Sink> sink) : name(std::move(loggerName)) {
            this->add_sink(sinkName, sink);
        }

        Logger(std::string name, std::pair<std::string, std::shared_ptr<Sinks::Sink>> sink) : name(std::move(name)) {
            this->add_sink(sink.first, sink.second);
        }

        Logger(std::string _name, std::vector<std::pair<std::string, std::shared_ptr<Sinks::Sink>>> sinkVec = {}) : name(std::move(_name)) {
            for (auto [name, sink]: sinkVec)
                add_sink(name, sink);
        }

        bool add_sink(std::string name, std::shared_ptr<Sinks::Sink> sink) {
            if (name.empty() || this->pipelines.count(name))
                return false;
            pipelines[name] = std::make_shared<LogPipeLine>(sink);
            return true;
        }

        void erase_sink(std::string name) { pipelines.erase(name); }
        void set_level(LogLevel _lvl) { this->lvl = _lvl; }
        void set_sink_level(std::string name, LogLevel lvl) {
            if (name.empty() || !pipelines.count(name))
                return;
            pipelines[name]->set_level(lvl);
        }

        void set_pattern(std::string pattern) {
            for (auto it: pipelines)
                it.second->set_pattern(pattern);
        }

        void set_pattern(std::string name, std::string pattern) {
            if (name.empty() || !pipelines.count(name))
                return;
            pipelines[name]->set_pattern(std::move(pattern));
        }

        template <typename... Args>
        void trace(std::format_string<Args...> fmt, Args&&... msgs) { log(LogLevel::TRACE, fmt, std::forward<Args>(msgs)...); }
        void trace(const std::string& msg) { log(LogLevel::TRACE, "{}", msg); }

        template <typename... Args>
        void debug(std::format_string<Args...> fmt, Args&&... msgs) { log(LogLevel::DEBUG, fmt, std::forward<Args>(msgs)...); }
        void debug(const std::string& msg) { log(LogLevel::DEBUG, "{}", msg); }

        template <typename... Args>
        void info(std::format_string<Args...> fmt, Args&&... msgs) { log(LogLevel::INFO, fmt, std::forward<Args>(msgs)...); }
        void info(const std::string& msg) { log(LogLevel::INFO, "{}", msg); }

        template <typename... Args>
        void warn(std::format_string<Args...> fmt, Args&&... msgs) { log(LogLevel::WARN, fmt, std::forward<Args>(msgs)...); }
        void warn(const std::string& msg) { log(LogLevel::WARN, "{}", msg); }

        template <typename... Args>
        void error(std::format_string<Args...> fmt, Args&&... msgs) { log(LogLevel::ERROR, fmt, std::forward<Args>(msgs)...); }
        void error(const std::string& msg) { log(LogLevel::ERROR, "{}", msg); }

        template <typename... Args>
        void critical(std::format_string<Args...> fmt, Args&&... msgs) { log(LogLevel::CRITICAL, fmt, std::forward<Args>(msgs)...); }
        void critical(const std::string& msg) { log(LogLevel::CRITICAL, "{}", msg); }

    private:
        bool shouldLog(LogLevel _lvl) {
            return this->lvl <= _lvl && !this->pipelines.empty();
        }

        LogEvent generate_event(LogLevel lvl, std::string msg, std::string file = "?", std::string func = "?", int line = -1) {
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
                    .subSec = static_cast<unsigned>(hms.subseconds().count())
                },
                .pos = {
                    .file = std::move(file),
                    .func = std::move(func),
                    .line = line
                }
            };

            return event;
        }

        template <typename... Args>
        void log(LogLevel _lvl, std::format_string<Args...> fmt, Args&&... msgs) {
            if (!shouldLog(_lvl))
                return;

            auto event = generate_event(_lvl, std::format(fmt, std::forward<Args>(msgs)...));

            for (const auto& [name, p]: pipelines)
                p->log(event);
        }

        template <typename... Args>
        void log(LogLevel _lvl, std::string file, std::string func, int line, std::format_string<Args...> fmt, Args&&... msgs) {
            if (!shouldLog(_lvl))
                return;

            auto event = generate_event(_lvl, std::format(fmt, std::forward<Args>(msgs)...), std::move(file), std::move(func), line);

            for (const auto& [name, p]: pipelines)
                p->log(event);
        }

    private:
        const std::string name;
        LogLevel lvl = LogLevel::INFO;
        std::unordered_map<std::string, std::shared_ptr<stslog::LogPipeLine>> pipelines;
    };

    inline std::shared_ptr<Logger> make_logger(std::string loggerName, std::string sinkName, std::shared_ptr<Sinks::Sink> sink) {
        return std::make_shared<Logger>(loggerName, sinkName, sink);
    }

    inline std::shared_ptr<Logger> make_logger(std::string name, std::pair<std::string, std::shared_ptr<Sinks::Sink>> sink) {
        return std::make_shared<Logger>(name, sink);
    }

    inline std::shared_ptr<Logger> make_logger(std::string name, std::vector<std::pair<std::string, std::shared_ptr<Sinks::Sink>>> sinkVec = {}) {
        return std::make_shared<Logger>(name, sinkVec);
    }

}
