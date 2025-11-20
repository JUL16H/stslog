#pragma once
#include <string>
#include <memory>
#include <vector>
#include <algorithm>
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

        constexpr void initPatternTrie()
        {

        }

        void set_pattern(std::string pattern)
        {
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
