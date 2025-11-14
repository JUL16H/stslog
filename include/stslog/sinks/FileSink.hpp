#pragma once

#include "stslog/Sink.hpp"
#include <fstream>

namespace stslog::Sinks
{
    class FileSink : public Sink
    {
    public:
        FileSink(std::string _file) : Sink(), file(std::move(_file)), fout(file, std::ios::app) { }
        void write(const LogEvent &event) override
        {
            // TODO: 异常捕获 缓冲区 线程安全
            fout << event.content;
            if (event.lvl != LogLevel::CRITICAL)
                fout << '\n';
            else
                fout << std::endl;
        }

    private:
        std::string file;
        std::ofstream fout;
    };
}
