#pragma once
#include <memory>
#include "stslog/Sink.hpp"
#include "stslog/FormatCombiner.hpp"

namespace stslog
{
    class LogPipeLine
    {
    public:
        LogPipeLine(std::shared_ptr<Sinks::Sink> _sink)
         : sink(_sink), formatter(std::make_shared<FormatCombiner>()) {}

        void log(LogEvent &event)
        {
            if (!shouldLog(event.lvl))
                return;
            event.content = formatter->content(event);
            sink->write(event);
        }

        void set_level(LogLevel _lvl) { lvl = _lvl; }

        void set_pattern(std::string pattern)
        {
            this->formatter->set_pattern(std::move(pattern));
        }

    private:
        bool shouldLog(LogLevel _lvl) { return this->lvl <= _lvl; }

    private:
        std::string name;
        std::shared_ptr<FormatCombiner> formatter;
        std::shared_ptr<Sinks::Sink> sink;
        LogLevel lvl = LogLevel::TRACE;
    };
}
