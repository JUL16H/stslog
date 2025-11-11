#include <string>
#include <vector>
#include <memory>
#include <format>
#include <chrono>
#include "stslog/LogLevel.hpp"

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
        struct
        {
            std::string file;
            std::string func;
            std::string line;
        } pos;
        std::string lvl;
        std::string msg;
        std::string threadID;
        std::string processID;
    };

    // struct Formatter { virtual std::string content(const LogInfo &info) = 0; };

    // struct Formatter_year : public Formatter
    // {
    //     std::string content(const LogInfo &info) override
    //     {
    //         return info.time.year;
    //     }
    // };

    // struct Formatter_month : public Formatter
    // {
    //     std::string content(const LogInfo &info) override
    //     {
    //         return info.time.month;
    //     }
    // };

    // struct Formatter_str : public Formatter
    // {
    // public:
    //     Formatter_str(std::string _str) : Formatter(), str(_str) {}
    //     std::string content(const LogInfo &info) override
    //     {
    //         return str;
    //     }

    //     private:
    //         std::string str;
    // };

    struct FormatterBase
    {
        virtual ~FormatterBase() = default;
        virtual std::string content(const LogInfo &info) = 0;
    };

    template <char... cs>
    struct Formatter : public FormatterBase
    {
        std::string content(const LogInfo &info) override { return ""; }
    };

    template <>
    class Formatter<'c'> : public FormatterBase
    {
    public:
        Formatter(const char _c) : c(_c) {};
        std::string content(const LogInfo &info) override
        {
            return std::string(1, c);
        }

    private:
        char c;
    };

    template <>
    struct Formatter<'%', 'Y'> : public FormatterBase
    {
        std::string content(const LogInfo &info) override
        {
            return info.time.year;
        }
    };

    template <>
    struct Formatter<'%', 'm'> : public FormatterBase
    {
        std::string content(const LogInfo &info) override
        {
            return info.time.month;
        }
    };

    template <>
    struct Formatter<'%', 'd'> : public FormatterBase
    {
        std::string content(const LogInfo &info) override
        {
            return info.time.day;
        }
    };

    template <>
    struct Formatter<'%', 'H'> : public FormatterBase
    {
        std::string content(const LogInfo &info) override
        {
            return info.time.hour;
        }
    };

    template <>
    struct Formatter<'%', 'M'> : public FormatterBase
    {
        std::string content(const LogInfo &info) override
        {
            return info.time.minute;
        }
    };

    template <>
    struct Formatter<'%', 'S'> : public FormatterBase
    {
        std::string content(const LogInfo &info) override
        {
            return info.time.sec;
        }
    };

    template <>
    struct Formatter<'%', 'l'> : public FormatterBase
    {
        std::string content(const LogInfo &info) override
        {
            return info.lvl;
        }
    };

    template <>
    struct Formatter<'%', 'v'>: public FormatterBase
    {
        std::string content(const LogInfo &info) override
        {
            return info.msg;
        }
    };
}

namespace stslog
{
    struct FormatCombiner
    {
    public:
        FormatCombiner()
        {
            this->set_format();
        }

        void set_format(std::string format = "")
        {
            if (format.empty())
                format = "[%H:%M:%S] [%l] %v";

            this->formatters.clear();
            this->formatters.reserve(0);

            //TODO
            bool f = false;
            for (const char c: format)
            {
                if (f)
                {
                    switch (c)
                    {
                    case 'Y':
                        this->formatters.push_back(std::make_unique<Formatter<'%', 'Y'>>()); break;
                    case 'm':
                        this->formatters.push_back(std::make_unique<Formatter<'%', 'm'>>()); break;
                    case 'd':
                        this->formatters.push_back(std::make_unique<Formatter<'%', 'd'>>()); break;
                    case 'H':
                        this->formatters.push_back(std::make_unique<Formatter<'%', 'H'>>()); break;
                    case 'M':
                        this->formatters.push_back(std::make_unique<Formatter<'%', 'M'>>()); break;
                    case 'S':
                        this->formatters.push_back(std::make_unique<Formatter<'%', 'S'>>()); break;
                    case 'l':
                        this->formatters.push_back(std::make_unique<Formatter<'%', 'l'>>()); break;
                    case 'v':
                        this->formatters.push_back(std::make_unique<Formatter<'%', 'v'>>()); break;
                    case '%':
                        this->formatters.push_back(std::make_unique<Formatter<'c'>>('%')); break;
                    // default:
                    //     this->formatters.push_back(std::make_unique<Formatter<'c'>>('%'));
                    //     this->formatters.push_back(std::make_unique<Formatter<'c'>>(c)); break;
                    }
                    f = false;
                }
                else
                {
                    if (c == '%')
                        f = true;
                    else
                        this->formatters.push_back(std::make_unique<Formatter<'c'>>(c));
                }
            }
        }

        std::string content(LogLevel lvl, std::string msg)
        {
            fillInfo(lvl, msg);

            std::string text;
            for (const auto& f: formatters)
                text.append(std::move(f->content(info)));
            return text;
        }

    private:
        void fillInfo(stslog::LogLevel lvl, std::string msg)
        {
            auto now = std::chrono::system_clock::now();
            info.time.year = std::format("{:%Y}", now);
            info.time.month = std::format("{:%m}", now);
            info.time.day = std::format("{:%d}", now);
            info.time.hour = std::format("{:%H}", now);
            info.time.minute = std::format("{:%M}", now);
            info.time.sec = std::format("{:%S}", floor<std::chrono::seconds>(now));
            info.lvl = lvl2str(lvl);
            info.msg = msg;
        };

        LogInfo info;
        std::vector<std::unique_ptr<FormatterBase>> formatters;
    };
}
