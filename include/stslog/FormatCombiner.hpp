#pragma once
#include <string>
#include <memory>
#include <vector>
#include "stslog/Formatter.hpp"

namespace stslog {

    class FormatCombiner {
    public:
        FormatCombiner() {
            this->set_pattern("+");
        }

        constexpr void initPatternTrie() {

        }

        void set_pattern(std::string pattern) {
            formatters.clear();

            if (pattern == "+")
                pattern = "[%H:%M:%S] [%l] %v";

            bool normal = true;
            for (const auto c: pattern) {
                if (normal) {
                    if (c != '%')
                        formatters.push_back(std::make_unique<Formatter<'c'>>(c));
                    else
                        normal = false;
                }
                else {
                    switch (c) {
                    case '%':
                        formatters.push_back(std::make_unique<Formatter<'c'>>('%'));
                        break;
                    case 'Y':
                        formatters.push_back(std::make_unique<Formatter<'%', 'Y'>>());
                        break;
                    case 'y':
                        formatters.push_back(std::make_unique<Formatter<'%', 'y'>>());
                        break;
                    case 'm':
                        formatters.push_back(std::make_unique<Formatter<'%', 'm'>>());
                        break;
                    case 'd':
                        formatters.push_back(std::make_unique<Formatter<'%', 'd'>>());
                        break;
                    case 'H':
                        formatters.push_back(std::make_unique<Formatter<'%', 'H'>>());
                        break;
                    case 'I':
                        formatters.push_back(std::make_unique<Formatter<'%', 'I'>>());
                        break;
                    case 'M':
                        formatters.push_back(std::make_unique<Formatter<'%', 'M'>>());
                        break;
                    case 'S':
                        formatters.push_back(std::make_unique<Formatter<'%', 'S'>>());
                        break;
                    case 'e':
                        formatters.push_back(std::make_unique<Formatter<'%', 'e'>>());
                        break;
                    case 'f':
                        formatters.push_back(std::make_unique<Formatter<'%', 'f'>>());
                        break;
                    case 'z':
                        formatters.push_back(std::make_unique<Formatter<'%', 'z'>>());
                        break;
                    case 'Z':
                        formatters.push_back(std::make_unique<Formatter<'%', 'Z'>>());
                        break;
                    case 'l':
                        formatters.push_back(std::make_unique<Formatter<'%', 'l'>>());
                        break;
                    case 't':
                        formatters.push_back(std::make_unique<Formatter<'%', 't'>>());
                        break;
                    case 'p':
                        formatters.push_back(std::make_unique<Formatter<'%', 'p'>>());
                        break;
                    case 'v':
                        formatters.push_back(std::make_unique<Formatter<'%', 'v'>>());
                        break;
                    default:
                        formatters.push_back(std::make_unique<Formatter<'s'>>("%?"));
                    }
                    normal = true;
                }
            }
        }

        std::string content(LogEvent event) {
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
