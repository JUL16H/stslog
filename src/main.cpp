#include "stslog/stslog.hpp"
#include "stslog/sinks/sinks.hpp"

int main()
{
    auto logger = stslog::make_logger(
        "logger", {
            stslog::make_sink<stslog::Sinks::StdoutSink>(),
            stslog::make_sink<stslog::Sinks::FileSink>("log.log")
        }
    );
    logger->set_format("[%Y-%m-%d %h:%m:%s] [%l] %v");
    logger->info("hello world");

    logger->set_level(stslog::LogLevel::OFF);
    logger->error("Error");

    return 0;
}
