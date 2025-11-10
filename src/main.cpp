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
    logger->info("hello world");

    return 0;
}
