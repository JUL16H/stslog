#pragma once
#include <string>
#include <memory>
#include "stslog/Formatter.hpp"
#include "stslog/LogLevel.hpp"

namespace stslog
{
    namespace Sinks
    {
        class Sink
        {
        public:
            virtual void write(std::shared_ptr<LogEvent> event) = 0;
            virtual ~Sink() = default;
        };
    }

    template <typename SinkType, typename... Args>
    std::shared_ptr<Sinks::Sink> make_sink(Args&&... args)
    {
        return std::make_shared<SinkType>(std::forward<Args>(args)...);
    }
}
