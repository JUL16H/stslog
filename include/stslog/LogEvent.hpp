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
            unsigned year;
            unsigned month;
            unsigned day;
            unsigned hour;
            unsigned minute;
            unsigned sec;
            unsigned ms;
        } time;
        struct
        {
            std::string file;
            std::string func;
            unsigned line;
        } pos;

        std::string content;

        void fillInfo()
        {
            // TODO: 现在不会更换时区，锁定为格林威治时间
            const auto now = std::chrono::system_clock::now();
            std::time_t t = std::chrono::system_clock::to_time_t(now);
            std::tm local_tm = *std::localtime(&t);

            time.year = local_tm.tm_year + 1900;
            time.month = local_tm.tm_mon + 1;
            time.day = local_tm.tm_mday;
            time.hour = local_tm.tm_hour;
            time.minute = local_tm.tm_min;
            time.sec = local_tm.tm_sec;
        }
    };
}
