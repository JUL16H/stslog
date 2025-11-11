#pragma once

#include "stslog/sinks/Sink.hpp"
#include <fstream>

namespace stslog::Sinks
{
    class FileSink : public Sink
    {
    public:
        FileSink(std::string _file) : Sink(), file(_file) {}
        void write(LogLevel lvl, std::string msg) override
        {
            // TODO 异常捕获 缓冲区 线程安全
            std::ofstream fout(file);
            fout << formatter.content(lvl, std::move(msg)) << std::endl;
        }

    private:
        std::string file;
    };
}
