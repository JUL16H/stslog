#include "stslog/stslog.hpp"
#include "stslog/sinks/sinks.hpp"

int main()
{
    auto logger = stslog::make_logger("logger", {new stslog::Sinks::StdoutSink(), new stslog::Sinks::FileSink("log.log")});
    logger->info("hello world");

    return 0;
}
