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
         : sink(_sink), formatter(std::make_shared<FormatCombiner>()) { }

    private:
        void log(std::shared_ptr<LogEvent> pevent)
        {
            pevent->fillInfo();
            pevent->content = formatter->content(pevent);
            sink->write(pevent);
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
