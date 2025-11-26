#pragma once
#include <string>
#include "stslog/LogLevel.hpp"

namespace stslog {

    struct LogEvent {
        LogLevel lvl;
        std::string msg;

        int threadID;
        int processID;

        struct {
            int year;
            unsigned month;
            unsigned day;
            unsigned hour;
            unsigned minute;
            unsigned sec;
            unsigned long long subSec;
        } time;
        struct {
            std::string file;
            std::string func;
            int line;
        } pos;

        std::string content;
    };

}
