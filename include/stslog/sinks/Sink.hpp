#pragma once

#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <format>

namespace stslog
{
    struct LogInfo
    {
        struct
        {
            std::string year;
            std::string month;
            std::string day;
            std::string hour;
            std::string minute;
            std::string sec;
            std::string msec;
        } time;
        std::string line;
        std::string lvl;
    };

    struct Formatter { virtual std::string content(const LogInfo &info) = 0; };
    struct Formatter_year : public Formatter
    {
        std::string content(const LogInfo &info) override
        {
            return info.time.year;
        }
    };

    struct FormatCombiner
    {
    public:
        void set_format(std::string pattern)
        {
            if (pattern.empty())
                pattern = "[%H:%M:%S] [%l] %c";

            //TODO
            this->formatters.clear();
            this->formatters.reserve(0);
            this->formatters.emplace_back(std::make_unique<Formatter_year>());
        }

        std::string content()
        {
            fillInfo();

            std::string msg;
            for (const auto& f: formatters)
                msg.append(std::move(f->content(info)));
            return msg;
        }

    private:
        void fillInfo()
        {
            auto now = std::chrono::system_clock::now();
            info.time.year = std::format("{:%Y}", now);
        };

        LogInfo info;
        std::vector<std::unique_ptr<Formatter>> formatters;
    };

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
