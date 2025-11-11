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
    class Formatter : public FormatterBase
    {
        std::string content(const LogInfo &info)
        {
            return std::string({cs...});
        }
    };

    template <>
    class Formatter<'c'> : public FormatterBase
    {
    public:
        Formatter(const char _c) : c(_c) {};
        std::string content(const LogInfo &info)
        {
            return std::string(1, c);
        }
    private:
        char c;
    };

    template <>
    class Formatter<'%', 'Y'> : public FormatterBase
    {
    public:
        std::string content(const LogInfo &info)
        {
            return info.time.year;
        }
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

            for (const char c: format)
                this->formatters.emplace_back(std::make_unique<Formatter<'c'>>(c));
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
        std::vector<std::unique_ptr<FormatterBase>> formatters;
    };
}
