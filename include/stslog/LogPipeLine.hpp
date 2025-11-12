#pragma once
#include <memory>
#include "stslog/Sink.hpp"
#include "stslog/LogLevel.hpp"
#include "stslog/FormatCombiner.hpp"

namespace stslog
{
    class LogPipeLine
    {
        friend class Logger;
    public:
        LogPipeLine(std::string _name, std::shared_ptr<Sinks::Sink> _sink)
         : name(std::move(_name)), sink(_sink)
        {
            formatter = std::make_shared<FormatCombiner>();
        }

    private:
        void log(std::shared_ptr<LogEvent> pevent)
        {
            pevent->fillInfo();
            pevent->content = formatter->content(pevent);
            sink->write(pevent);
        }

    private:
        std::string name;
        std::shared_ptr<FormatCombiner> formatter;
        std::shared_ptr<Sinks::Sink> sink;

    };
}
