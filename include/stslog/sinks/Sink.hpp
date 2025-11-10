#pragma once

#include <string>
#include <memory>

namespace stslog
{
    namespace Sinks
    {
        class Sink
        {
        public:
            virtual void write(std::string text) = 0;
            virtual ~Sink() = default;
        };
    }

    template <typename SinkType, typename... Args>
    std::shared_ptr<Sinks::Sink> make_sink(Args&&... args)
    {
        return std::make_shared<SinkType>(std::forward<Args>(args)...);
    }
}
