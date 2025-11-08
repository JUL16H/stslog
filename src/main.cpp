#include "stslog/stslog.hpp"

int main()
{
    auto logger = stslog::make_logger("logger", {new stslog::Sinks::StdoutSink(), new stslog::Sinks::StdoutSink});
    logger->info("hello world");

    return 0;
}
