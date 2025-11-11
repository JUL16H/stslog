#pragma once

#include <string>
#include <vector>
#include <memory>
#include "stslog/LogLevel.hpp"
#include "stslog/sinks/Sink.hpp"

namespace stslog
{
    class Logger
    {
    public:
        Logger(std::string _name) : name(std::move(_name)) {}
        Logger(std::string _name, std::shared_ptr<Sinks::Sink> sink) : name(std::move(_name))
         { this->sinks.emplace_back(sink); }
        Logger(std::string _name, std::vector<std::shared_ptr<Sinks::Sink>> _sinks)
         : name(std::move(_name)), sinks(std::move(_sinks)) {}

        void set_level(LogLevel _lvl) { this->lvl = _lvl; }
        void reset_format()
        {
            for (auto& s: this->sinks)
                s->set_format("");
        }
        void set_format(std::string format)
        {
            for (auto& s: this->sinks)
                s->set_format(format);
        }

        void trace(std::string msg) { log(LogLevel::TRACE, msg); }
        void debug(std::string msg) { log(LogLevel::DEBUG, msg); }
        void info(std::string msg) { log(LogLevel::INFO, msg); }
        void warn(std::string msg) { log(LogLevel::WARN, msg); }
        void error(std::string msg) { log(LogLevel::ERROR, msg); }
        void critical(std::string msg) { log(LogLevel::CRITICAL, msg); }

        void change_sink(std::shared_ptr<Sinks::Sink> _sink)
        {
            this->sinks.clear();
            this->sinks.emplace_back(_sink);
        }
        void change_sink(std::vector<std::shared_ptr<Sinks::Sink>> _sinks) noexcept
         { this->sinks = std::move(_sinks); }

    private:
        void log(LogLevel _lvl, std::string msg)
        {
            // TODO: 添加额外信息和格式, 支持内容格式化
            if (_lvl < this->lvl) return;
            for (const auto &s: this->sinks)
                s->write(_lvl, msg);
        }

        std::string name;
        LogLevel lvl = LogLevel::INFO;
        std::vector<std::shared_ptr<Sinks::Sink>> sinks;
    };

    inline std::shared_ptr<Logger> make_logger(std::string name)
    {
        return std::make_shared<Logger>(std::move(name));
    }

    inline std::shared_ptr<Logger> make_logger(std::string name, std::shared_ptr<Sinks::Sink> sink)
    {
        return std::make_shared<Logger>(std::move(name), std::move(sink));
    }

    inline std::shared_ptr<Logger> make_logger(std::string name, std::vector<std::shared_ptr<Sinks::Sink>> sinks)
    {
        return std::make_shared<Logger>(std::move(name), std::move(sinks));
    }

    // inline std::shared_ptr<Logger> make_logger(std::string name, Sinks::Sink* sink)
    // {
    //     std::vector<std::shared_ptr<Sinks::Sink>> sinksVec;
    //     sinksVec.reserve(1);
    //     sinksVec.emplace_back(std::shared_ptr<Sinks::Sink>(sink));
    //     auto logger = std::make_shared<Logger>(std::move(name), std::move(sinksVec));
    //     return logger;
    // }

    // inline std::shared_ptr<Logger> make_logger(std::string name, std::vector<Sinks::Sink*> sinks)
    // {
    //     std::vector<std::shared_ptr<Sinks::Sink>> sinksVec;
    //     sinksVec.reserve(sinks.size());
    //     std::ranges::transform(sinks, std::back_inserter(sinksVec),
    //         [](auto* p){ return std::shared_ptr<Sinks::Sink>(p); });
    //     auto logger = std::make_shared<Logger>(std::move(name), std::move(sinksVec));
    //     return logger;
    // }
}
