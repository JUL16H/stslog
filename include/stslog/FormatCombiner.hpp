#pragma once

#include <string>
#include "stslog/Formatter.hpp"

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

        std::string content(const std::shared_ptr<LogEvent> pevent)
        {
            std::string text;
            for (const auto& f: formatters)
                text.append(std::move(f->content(*pevent)));
            return text;
        }

    private:

        std::vector<std::unique_ptr<FormatterBase>> formatters;
    };
}
