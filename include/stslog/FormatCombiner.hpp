#pragma once
#include <string>
#include <memory>
#include <vector>
#include "stslog/Formatter.hpp"

namespace stslog
{
    class FormatCombiner
    {
    public:
        FormatCombiner()
        {
            this->set_pattern("+");
        }

        void set_pattern(std::string pattern)
        {
            if (pattern == "+")
                pattern = "[%H:%M:%S] [%l] %v";

            this->formatters.clear();

            //TODO
            bool f = false;
            for (const char c: pattern)
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
                    case 'e':
                        this->formatters.push_back(std::make_unique<Formatter<'%', 'e'>>()); break;
                    case 'f':
                        this->formatters.push_back(std::make_unique<Formatter<'%', 'f'>>()); break;
                    case 'l':
                        this->formatters.push_back(std::make_unique<Formatter<'%', 'l'>>()); break;
                    case 'v':
                        this->formatters.push_back(std::make_unique<Formatter<'%', 'v'>>()); break;
                    case '%':
                        this->formatters.push_back(std::make_unique<Formatter<'c'>>('%')); break;
                    default:
                        this->formatters.push_back(std::make_unique<Formatter<'c'>>('%'));
                        this->formatters.push_back(std::make_unique<Formatter<'c'>>('?')); break;
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

        std::string content(LogEvent event)
        {
            std::string text;
            text.reserve(256);
            for (const auto& f: formatters)
                text += f->content(event);
            return text;
        }

    private:
        std::vector<std::unique_ptr<FormatterBase>> formatters;
    };
}
