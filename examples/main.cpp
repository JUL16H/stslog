#include <iostream>
#include "stslog/stslog.hpp"
#include "stslog/sinks.hpp"

void bar()
{
    for (int i = 0; i < 80; i++)
        std::cout << "=";
    std::cout << '\n';
}

void basic_use()
{
    stslog::Logger logger("logger", {
        {"file", stslog::make_sink<stslog::Sinks::FileSink>("log.log")},
        {"colored stdout", stslog::make_sink<stslog::Sinks::ColoredStdoutSink>()},
    });

    logger.set_format("[%Y-%m-%d %H:%M:%S:%e] [%l] %v");
    logger.set_level(stslog::LogLevel::TRACE);

    logger.trace("hello stslog");
    logger.debug("hello stslog");
    logger.info("hello stslog");
    logger.warn("hello stslog");
    logger.error("hello stslog");
    logger.critical("hello stslog");

    logger.set_format("");
    logger.info("{} + {} = {}", 2, 3, 5);

    logger.set_level(stslog::LogLevel::OFF);
    logger.error("off");
}

void use_registry()
{
    auto logger = stslog::make_logger("logger", "colored sink", stslog::make_sink<stslog::Sinks::ColoredStdoutSink>());
    stslog::LogRegistry::instance().enroll_logger(logger);
    logger->set_format("%v");

    auto logger_in_registry = stslog::LogRegistry::instance().get_logger("logger");
    logger_in_registry->info("hello stslog");
}

int main()
{
    basic_use(); bar();
    use_registry(); bar();
    return 0;
}
