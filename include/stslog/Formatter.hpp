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

    template <>
    struct Formatter<'%', 'Y'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return std::to_string(event.time.year);
        }
    };

    template <>
    struct Formatter<'%', 'm'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return std::to_string(event.time.month);
        }
    };

    template <>
    struct Formatter<'%', 'd'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return std::to_string(event.time.day);
        }
    };

    template <>
    struct Formatter<'%', 'H'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return std::to_string(event.time.hour);
        }
    };

    template <>
    struct Formatter<'%', 'M'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return std::to_string(event.time.minute);
        }
    };

    template <>
    struct Formatter<'%', 'S'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return std::to_string(event.time.sec);
        }
    };

    template <>
    struct Formatter<'%', 'l'> : public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return lvl2str(event.lvl);
        }
    };

    template <>
    struct Formatter<'%', 'v'>: public FormatterBase
    {
        std::string content(const LogEvent &event) override
        {
            return event.msg;
        }
    };
}
