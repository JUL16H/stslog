#pragma once
#include <memory>
#include "stslog/Sink.hpp"
#include "stslog/FormatCombiner.hpp"

namespace stslog
{
    class LogPipeLine
    {
        friend class Logger;
    public:
        LogPipeLine(std::shared_ptr<Sinks::Sink> _sink)
         : sink(_sink), formatter(std::make_shared<FormatCombiner>()) {}

    private:
        void log(LogEvent &event)
        {
            event.content = formatter->content(event);
            sink->write(event);
        }

        void set_format(std::string format)
        {
            this->formatter->set_format(std::move(format));
        }

    private:
        std::string name;
        std::shared_ptr<FormatCombiner> formatter;
        std::shared_ptr<Sinks::Sink> sink;

    };
}
