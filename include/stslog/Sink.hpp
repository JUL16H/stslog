#pragma once
#include <memory>
#include "stslog/LogEvent.hpp"

namespace stslog {
    namespace Sinks {
        class Sink {
        public:
            virtual void write(const LogEvent &event) = 0;
            virtual ~Sink() = default;
        };
    }

    template <typename SinkType, typename... Args>
    std::shared_ptr<Sinks::Sink> make_sink(Args&&... args) {
        return std::make_shared<SinkType>(std::forward<Args>(args)...);
    }
}
