#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "stslog/Logger.hpp"
#include "stslog/sinks/ColoredStdoutSink.hpp"

namespace stslog {

    class LogRegistry {
    public:
        static LogRegistry& instance() {
            static LogRegistry inst;
            inst.enroll_logger(make_logger("default", "default sink", make_sink<Sinks::ColoredStdoutSink>()));
            return inst;
        }

        bool enroll_logger(std::shared_ptr<Logger> logger) {
            if (logger->name.empty() || loggerMap.count(logger->name))
                return false;
            loggerMap[logger->name] = logger;
            return true;
        }

        std::shared_ptr<Logger> get_logger(std::string name) {
            std::shared_ptr<Logger> rst = nullptr;
            if (!name.empty() && loggerMap.count(name) && name != "default")
                rst = loggerMap[name];
            return rst;
        }

        void erase_logger(std::string name)
        {
            if (!loggerMap.count(name) || name == "default")
                return;
            loggerMap.erase(name);
        }

    private:
        std::unordered_map<std::string, std::shared_ptr<Logger>> loggerMap;

    private:
        LogRegistry() = default;
        ~LogRegistry() = default;
        LogRegistry(const LogRegistry&) = delete;
        LogRegistry& operator=(const LogRegistry&) = delete;
    };

}
