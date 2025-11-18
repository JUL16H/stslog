#pragma once
#include <string>
#include <vector>

namespace stslog
{
    class PatternAC
    {
    public:
        constexpr void init()
        {
            exist.resize(100, false);
            trie.resize(100, std::vector<int>(256, 0));


        }
    private:
        std::vector<bool> exist;
        std::vector<std::vector<int>> trie;
    };
}
