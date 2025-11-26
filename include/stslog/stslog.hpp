#pragma once
#include "stslog/Logger.hpp"
#include "stslog/LogRegistry.hpp"

namespace stslog {
    template <typename... Args>
    inline void trace(std::format_string<Args...> fmt, Args&&... msgs) {
        LogRegistry::instance().get_logger("default")->trace(fmt, std::forward<Args>(msgs)...);
    }
    inline void trace(const std::string& msg) {
        LogRegistry::instance().get_logger("default")->trace("{}", msg);
    }

    template <typename... Args>
    inline void debug(std::format_string<Args...> fmt, Args&&... msgs) {
        LogRegistry::instance().get_logger("default")->debug(fmt, std::forward<Args>(msgs)...);
    }
    inline void debug(const std::string& msg) {
        LogRegistry::instance().get_logger("default")->debug("{}", msg);
    }

    template <typename... Args>
    void info(std::format_string<Args...> fmt, Args&&... msgs) {
        LogRegistry::instance().get_logger("default")->info(fmt, std::forward<Args>(msgs)...);
    }
    inline void info(const std::string& msg) {
        LogRegistry::instance().get_logger("default")->info("{}", msg);
    }

    template <typename... Args>
    void warn(std::format_string<Args...> fmt, Args&&... msgs) {
        LogRegistry::instance().get_logger("default")->warn(fmt, std::forward<Args>(msgs)...);
    }
    inline void warn(const std::string& msg) {
        LogRegistry::instance().get_logger("default")->warn("{}", msg);
    }

    template <typename... Args>
    void error(std::format_string<Args...> fmt, Args&&... msgs) {
        LogRegistry::instance().get_logger("default")->error(fmt, std::forward<Args>(msgs)...);
    }
    inline void error(const std::string& msg) {
        LogRegistry::instance().get_logger("default")->error("{}", msg);
    }

    template <typename... Args>
    void critical(std::format_string<Args...> fmt, Args&&... msgs) {
        LogRegistry::instance().get_logger("default")->critical(fmt, std::forward<Args>(msgs)...);
    }
    inline void critical(const std::string& msg) {
        LogRegistry::instance().get_logger("default")->critical("{}", msg);
    }
}
