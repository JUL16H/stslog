#include "stslog/stslog.hpp"
#include "stslog/sinks.hpp"

int main()
{
    // auto logger = stslog::make_logger(
    //     "logger", {
    //         // stslog::make_sink<stslog::Sinks::StdoutSink>(),
    //         stslog::make_sink<stslog::Sinks::ColoredStdoutSink>(),
    //         stslog::make_sink<stslog::Sinks::FileSink>("log.log")
    //     }
    // );

    stslog::Logger logger("logger");
    logger.add_sink("stdout", stslog::make_sink<stslog::Sinks::ColoredStdoutSink>());
    logger.add_sink("file", stslog::make_sink<stslog::Sinks::FileSink>("log.log"));

    // logger->set_format("[%Y-%m-%d %H:%M:%S] [%l] %v");
    logger.set_level(stslog::LogLevel::TRACE);
    logger.trace("hello world");
    logger.debug("hello world");
    logger.info("hello world");
    logger.warn("hello world");
    logger.error("hello world");
    logger.critical("hello world");

    logger.set_level(stslog::LogLevel::OFF);
    logger.error("off");

    return 0;
}
