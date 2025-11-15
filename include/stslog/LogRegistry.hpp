#include <string>
#include <unordered_map>
#include <memory>
#include "stslog/Logger.hpp"
#include "stslog/sinks/ColoredStdoutSink.hpp"

namespace stslog
{
    class LogRegistry
    {
    public:
        static LogRegistry& instance()
        {
            static LogRegistry inst;
            inst.loggerMap["default"] = make_logger("default", "colored stdout sink", make_sink<Sinks::ColoredStdoutSink>());
            return inst;
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
