#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <memory>
#include "stslog/sinks/Sink.hpp"

namespace stslog
{
    enum class LogLevel : std::uint8_t
    {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        CRITICAL,
        OFF
    };

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
            // TODO: 添加额外信息和格式, 支持内容格式化
            if (this->lvl >= _lvl)
                for (auto s: this->sinks)
                    s->write(text);
        }

        std::string name;
        LogLevel lvl = LogLevel::INFO;
        std::vector<std::shared_ptr<Sinks::Sink>> sinks;
    };

    inline std::shared_ptr<Logger> make_logger(std::string name, Sinks::Sink* sink)
    {
        std::vector<std::shared_ptr<Sinks::Sink>> sinksVec;
        sinksVec.reserve(1);
        sinksVec.emplace_back(std::shared_ptr<Sinks::Sink>(sink));
        auto logger = std::make_shared<Logger>(name, sinksVec);
        return logger;
    }

    // TODO
    inline std::shared_ptr<Logger> make_logger(std::string name, std::vector<Sinks::Sink*> sinks)
    {
        std::vector<std::shared_ptr<Sinks::Sink>> sinksVec;
        sinksVec.reserve(sinks.size());
        std::ranges::transform(sinks, std::back_inserter(sinksVec),
            [](auto* p){ return std::shared_ptr<Sinks::Sink>(p); });
        auto logger = std::make_shared<Logger>(name, sinksVec);
        return logger;
    }
}
