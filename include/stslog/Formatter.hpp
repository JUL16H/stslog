#pragma once
#include <string>
#include <vector>
#include <memory>
#include "stslog/LogEvent.hpp"

namespace stslog
{
    struct FormatterBase
    {
        virtual ~FormatterBase() = default;
        virtual std::string content(const LogEvent &event) = 0;
    };

    template <char... cs>
    struct Formatter : public FormatterBase
    {
        std::string content(const LogEvent &event) override { return ""; }
    };

    // 生字符
    template <>
    class Formatter<'c'> : public FormatterBase
    {
    public:
        Formatter(const char _c) : c(_c) {};
        std::string content(const LogEvent&) override
        {
            return std::string(1, c);
        }

    private:
        char c;
    };

    // 生字符串
    template <>
    class Formatter<'s'> : public FormatterBase
    {
    public:
        Formatter(std::string _s) : s(std::move(_s)) {};
        std::string content(const LogEvent&) override
        {
            return s;
        }

    private:
        std::string s;
    };


    // 年
    template <>
    struct Formatter<'%', 'Y'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return std::to_string(event.time.year);
        }
    };

    // 年(后2位)
    template <>
    struct Formatter<'%', 'y'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return std::to_string(event.time.year % 100);
        }
    };

    // 月
    template <>
    struct Formatter<'%', 'm'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return std::to_string(event.time.month);
        }
    };

    // 日
    template <>
    struct Formatter<'%', 'd'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return std::to_string(event.time.day);
        }
    };

    // 小时(24h)
    template <>
    struct Formatter<'%', 'H'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return std::to_string(event.time.hour);
        }
    };

    // 小时(12h)
    template <>
    struct Formatter<'%', 'I'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return std::to_string(event.time.hour % 12);
        }
    };

    // 分钟
    template <>
    struct Formatter<'%', 'M'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return std::to_string(event.time.minute);
        }
    };

    // 秒
    template <>
    struct Formatter<'%', 'S'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return std::to_string(event.time.sec);
        }
    };

    // 毫秒
    template <>
    struct Formatter<'%', 'e'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return std::to_string(event.time.subSec);
        }
    };

    // 微秒
    template <>
    struct Formatter<'%', 'f'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return {};
        }
    };

    // 时区
    template <>
    struct Formatter<'%', 'z'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return {};
        }
    };

    // 时区名
    template <>
    struct Formatter<'%', 'Z'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return {};
        }
    };

    // %Y-%m-%d
    template <>
    struct Formatter<'%', 'F'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return {};
        }
    };

    // %H:%M:%S
    template <>
    struct Formatter<'%', 'T'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return {};
        }
    };

    // 日志等级
    template <>
    struct Formatter<'%', 'l'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return lvl2str(event.lvl);
        }
    };

    // 线程号
    template <>
    struct Formatter<'%', 't'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return {};
        }
    };

    // 进程号
    template <>
    struct Formatter<'%', 'p'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return {};
        }
    };

    // 日志内容
    template <>
    struct Formatter<'%', 'v'>: public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return event.msg;
        }
    };
}
