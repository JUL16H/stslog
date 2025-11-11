#include <string>
#include <vector>
#include <memory>
#include <format>
#include <chrono>

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
        std::string msg;
    };

    struct Formatter { virtual std::string content(const LogInfo &info) = 0; };

    struct Formatter_year : public Formatter
    {
        std::string content(const LogInfo &info) override
        {
            return info.time.year;
        }
    };

    struct Formatter_month : public Formatter
    {
        std::string content(const LogInfo &info) override
        {
            return info.time.month;
        }
    };

    struct Formatter_str : public Formatter
    {
    public:
        Formatter_str(std::string _str) : Formatter(), str(_str) {}
        std::string content(const LogInfo &info) override
        {
            return str;
        }

        private:
            std::string str;
    };
}

namespace stslog
{
    struct FormatCombiner
    {
    public:
        void set_format(std::string format)
        {
            if (format.empty())
                format = "[%H:%M:%S] [%l] %c";

            //TODO
            this->formatters.clear();
            this->formatters.reserve(0);

            for (const auto c: format)
                this->formatters.emplace_back(std::make_unique<Formatter_str>(std::string(1, c)));
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
}
