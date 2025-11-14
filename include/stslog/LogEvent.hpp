#pragma once
#include <string>
#include "stslog/LogLevel.hpp"
#include <chrono>

namespace stslog
{
    struct LogEvent
    {
        LogLevel lvl;
        std::string msg;

        int threadID;
        int processID;

        struct
        {
            int year;
            unsigned month;
            unsigned day;
            unsigned hour;
            unsigned minute;
            unsigned sec;
            unsigned long long ms;
        } time;
        struct
        {
            std::string file;
            std::string func;
            int line;
        } pos;

        std::string content;

        void fillInfo(LogLevel _lvl, std::tm tm, std::string _msg, std::string file, std::string func, int line)
        {
            lvl = _lvl;
            msg = _msg;

            time.year = tm.tm_year + 1900;
            time.month = tm.tm_mon + 1;
            time.day = tm.tm_mday;
            time.hour = tm.tm_hour;
            time.minute = tm.tm_min;
            time.sec = tm.tm_sec;
            // TODO
            // time.ms = static_cast<unsigned>((std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000).count());

            pos.file = file;
            pos.func = func;
            pos.line = line;
        }
    };
}
