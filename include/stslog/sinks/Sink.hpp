#pragma once

#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <format>
#include "stslog/sinks/Formatter.hpp"

namespace stslog
{

    namespace Sinks
    {
        class Sink
        {
        public:
            virtual void write(std::string msg) = 0;
            virtual ~Sink() = default;

            void set_format(std::string format)
            {
                this->formatter.set_format(format);
            }

        protected:
            FormatCombiner formatter;
        };
    }

    template <typename SinkType, typename... Args>
    std::shared_ptr<Sinks::Sink> make_sink(Args&&... args)
    {
        return std::make_shared<SinkType>(std::forward<Args>(args)...);
    }
}
