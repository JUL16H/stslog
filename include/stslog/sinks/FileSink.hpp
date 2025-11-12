#pragma once

#include "stslog/Sink.hpp"
#include <fstream>

namespace stslog::Sinks
{
    class FileSink : public Sink
    {
    public:
        FileSink(std::string _file) : Sink(), file(_file) {}
        void write(std::shared_ptr<LogEvent> pevent) override
        {
            // TODO 异常捕获 缓冲区 线程安全
            std::ofstream fout(file);
            fout << pevent->content << std::endl;
        }

    private:
        std::string file;
    };
}
